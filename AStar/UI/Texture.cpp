#include "Texture.h"
#include "Sprite.h"
#include "../Device/Renderer.h"
#include "../Shader/Shader.h"
#include "../System/Buffer.h"
#include "../System/BufferDesc.h"
#include "../System/Direct3D11.h"
#include "../System/Game.h"
#include "../System/InputElement.h"
#include "../System/SubResourceDesc.h"
#include "../System/VertexStreamDesc.h"

Texture::Texture() :
    mTexture(nullptr),
    mVertexLayout(nullptr) {
}

Texture::~Texture() {
    SAFE_RELEASE(mTexture);
}

void Texture::createVertexLayout(ID3D10Blob* compiledShader) {
    static constexpr InputElementDesc layout[] = {
        { "POSITION", 0, VertexType::VERTEX_TYPE_FLOAT3, 0, 0, SlotClass::SLOT_CLASS_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, VertexType::VERTEX_TYPE_FLOAT2, 0, sizeof(float) * 3, SlotClass::SLOT_CLASS_VERTEX_DATA, 0 },
    };
    constexpr unsigned numElements = sizeof(layout) / sizeof(layout[0]);
    mVertexLayout = Renderer::createInputLayout(layout, numElements, compiledShader);
}

void Texture::end() {
    SAFE_RELEASE(mSampleLinear);
}

void Texture::drawAll(std::list<std::shared_ptr<Sprite>>* sprites) {
    if (!mVertexBuffer || sprites->size() < 1) {
        return;
    }
    //プロジェクション
    Matrix4 proj = Matrix4::identity;
    //原点をスクリーン左上にするために平行移動
    proj.mat[3][0] = -1.f;
    proj.mat[3][1] = 1.f;
    //ピクセル単位で扱うために
    proj.mat[0][0] = 2.f / Game::WINDOW_WIDTH;
    proj.mat[1][1] = -2.f / Game::WINDOW_HEIGHT;

    //プリミティブ・トポロジーをセット
    Renderer::setPrimitive(PrimitiveType::PRIMITIVE_TYPE_TRIANGLE_STRIP);
    //バーテックスバッファーをセット
    VertexStreamDesc stream;
    stream.buffer = mVertexBuffer;
    stream.offset = 0;
    stream.stride = sizeof(TextureVertex);
    Renderer::setVertexBuffer(&stream);
    //インデックスバッファーをセット
    Renderer::setIndexBuffer(mIndexBuffer);
    //サンプラーのセット
    Direct3D11::mDeviceContext->PSSetSamplers(0, 1, &mSampleLinear);

    for (auto itr = sprites->begin(); itr != sprites->end(); ++itr) {
        auto sprite = (*itr);
        if (sprite->getState() == SpriteState::DEAD || sprite->getState() == SpriteState::INACTIVE) {
            continue;
        }
        sprite->onceToDead();

        auto shader = sprite->shader();
        //自身を使用するシェーダーとして登録
        shader->setVSShader();
        shader->setPSShader();
        //コンスタントバッファーを使うシェーダーの登録
        shader->setVSConstantBuffers();
        shader->setPSConstantBuffers();
        //頂点レイアウトをセット
        Renderer::setInputLayout(sprite->texture()->mVertexLayout);

        //シェーダーのコンスタントバッファーに各種データを渡す
        D3D11_MAPPED_SUBRESOURCE pData;
        if (SUCCEEDED(Direct3D11::mDeviceContext->Map(shader->getConstantBuffer()->buffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
            TextureShaderConstantBuffer cb;
            //ワールド、カメラ、射影行列を渡す
            cb.mWorld = sprite->getWorld();
            cb.mWorld.transpose();
            cb.mProjection = proj;
            cb.mProjection.transpose();
            cb.mColor = sprite->getColor();
            cb.mUV = sprite->getUV();
            memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
            Direct3D11::mDeviceContext->Unmap(shader->getConstantBuffer()->buffer(), 0);
        }
        //テクスチャーをシェーダーに渡す
        shader->setPSTextures(sprite->texture());
        //プリミティブをレンダリング
        Renderer::drawIndexed(6);
    }
}

ID3D11ShaderResourceView* Texture::texture() const {
    return mTexture;
}

const TextureDesc& Texture::desc() const {
    return mDesc;
}

void Texture::create(const char* fileName) {
    if (!mVertexBuffer) {
        //バーテックスバッファー作成
        createVertexBuffer();
        //インデックスバッファの作成
        createIndexBuffer();
        //テクスチャー用サンプラー作成
        createSampler();
    }
    //テクスチャー作成
    createTexture(fileName);
}

void Texture::createVertexBuffer() {
    static const TextureVertex vertices[] = {
        Vector3(0.f, 0.f, 0.f), Vector2(0.f, 0.f), //左上
        Vector3(1.f, 0.f, 0.f), Vector2(1.f, 0.f), //右上
        Vector3(0.f, 1.f, 0.f), Vector2(0.f, 1.f), //左下
        Vector3(1.f, 1.f, 0.f), Vector2(1.f, 1.f), //右下
    };

    BufferDesc bd;
    bd.size = sizeof(TextureVertex) * 4;
    bd.usage = BufferUsage::BUFFER_USAGE_IMMUTABLE;
    bd.type = BufferType::BUFFER_TYPE_VERTEX;

    SubResourceDesc sub;
    sub.data = vertices;
    mVertexBuffer = Renderer::createBuffer(bd, &sub);
}

void Texture::createIndexBuffer() {
    static constexpr unsigned short indices[] = {
        0, 1, 2,
        1, 3, 2
    };
    BufferDesc bd;
    bd.size = sizeof(indices);
    bd.usage = BufferUsage::BUFFER_USAGE_IMMUTABLE;
    bd.type = BufferType::BUFFER_TYPE_INDEX;

    SubResourceDesc sub;
    sub.data = indices;
    mIndexBuffer = Renderer::createBuffer(bd, &sub);
}

void Texture::createSampler() {
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    Direct3D11::mDevice->CreateSamplerState(&sd, &mSampleLinear);
}

void Texture::createTexture(const char* fileName) {
    setTextureDirectory();
    //ファイルからテクスチャ情報を取得
    D3DX11_IMAGE_INFO info;
    D3DX11GetImageInfoFromFileA(fileName, nullptr, &info, nullptr);

    mDesc.width = info.Width;
    mDesc.height = info.Height;

    if (FAILED(D3DX11CreateShaderResourceViewFromFileA(Direct3D11::mDevice, fileName, &toImageLoadInfo(mDesc), nullptr, &mTexture, nullptr))) {
        MessageBox(0, L"テクスチャ作成失敗", NULL, MB_OK);
    }
}

D3DX11_IMAGE_LOAD_INFO Texture::toImageLoadInfo(const TextureDesc& desc) const {
    D3DX11_IMAGE_LOAD_INFO info;
    info.Width = desc.width;
    info.Height = desc.height;
    info.Depth = desc.depth;
    info.FirstMipLevel = desc.firstMipLevel;
    info.MipLevels = desc.mipLevels;
    info.Usage = toUsage(desc.usage);
    info.BindFlags = toBind(desc.bindFlags);
    info.CpuAccessFlags = toCPUAccess(desc.cpuAccessFlags);
    info.MiscFlags = desc.miscFlags;
    info.Format = toFormat(desc.format);
    info.Filter = toFilter(desc.filter);
    info.MipFilter = toFilter(desc.mipFilter);
    info.pSrcInfo = desc.srcInfo;

    return info;
}

D3D11_USAGE Texture::toUsage(TextureUsage usage) const {
    static const D3D11_USAGE usages[] = {
        D3D11_USAGE_DEFAULT,
        D3D11_USAGE_IMMUTABLE,
        D3D11_USAGE_DYNAMIC,
        D3D11_USAGE_STAGING
    };
    return usages[static_cast<unsigned>(usage)];
}

unsigned Texture::toBind(TextureBind bind) const {
    static const unsigned binds[] = {
        D3D11_BIND_SHADER_RESOURCE,
        D3D11_BIND_RENDER_TARGET,
    };
    return binds[static_cast<unsigned>(bind)];
}

unsigned Texture::toCPUAccess(TextureCPUAccessFlag flag) const {
    static const unsigned accesses[] = {
        0,
        D3D11_CPU_ACCESS_WRITE,
        D3D11_CPU_ACCESS_READ
    };
    return accesses[static_cast<unsigned>(flag)];
}

DXGI_FORMAT Texture::toFormat(TextureFormat format) const {
    static const DXGI_FORMAT formats[] = {
        DXGI_FORMAT_R8G8B8A8_UNORM,
    };
    return formats[static_cast<unsigned>(format)];
}

unsigned Texture::toFilter(TextureFilter filter) const {
    static const unsigned filters[] = {
        D3DX11_FILTER_POINT,
        D3DX11_FILTER_LINEAR,
        D3DX11_FILTER_TRIANGLE,
    };
    return filters[static_cast<unsigned>(filter)];
}

ID3D11SamplerState* Texture::mSampleLinear = nullptr;
std::shared_ptr<Buffer> Texture::mVertexBuffer = nullptr;
std::shared_ptr<Buffer> Texture::mIndexBuffer = nullptr;
