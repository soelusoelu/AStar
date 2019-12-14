#pragma once

#include "../System/DirectXIncLib.h"
#include <memory>

class Buffer;
class Texture;

class Shader {
public:
    Shader();
    ~Shader();
    //シェーダの生成
    ID3D11VertexShader* createVertexShader(const char* fileName, const char* funcName);
    ID3D11PixelShader* createPixelShader(const char* fileName, const char* funcName);
    //自身をシェーダーとして登録
    void setVSShader(ID3D11ClassInstance* classInstances = nullptr, unsigned numClassInstances = 0);
    void setPSShader(ID3D11ClassInstance* classInstances = nullptr, unsigned numClassInstances = 0);
    //使用するコンスタントバッファを登録
    void setVSConstantBuffers(unsigned start = 0, unsigned numBuffers = 1);
    void setPSConstantBuffers(unsigned start = 0, unsigned numBuffers = 1);
    //テクスチャの登録
    void setVSTextures(std::shared_ptr<Texture> texture, unsigned start = 0, unsigned numTextures = 1);
    void setPSTextures(std::shared_ptr<Texture> texture, unsigned start = 0, unsigned numTextures = 1);
    //シェーダの取得
    ID3D11VertexShader* getVertexShader() const;
    ID3D11PixelShader* getPixelShader() const;
    //コンパイル済みシェーダの取得
    ID3D10Blob* getCompiledShader() const;
    //コンスタントバッファの取得
    std::shared_ptr<Buffer> getConstantBuffer() const;

private:
    ID3D10Blob* mCompileShader;
    ID3D11VertexShader* mVertexShader;
    ID3D11PixelShader* mPixelShader;
    std::shared_ptr<Buffer> mConstantBuffer;
};

