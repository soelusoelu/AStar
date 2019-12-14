#pragma once

#include "../Utility/Math.h"
#include "../System/DirectXIncLib.h"
#include <memory>
#include <string>
#include <unordered_map>

enum class PrimitiveType {
    PRIMITIVE_TYPE_POINT_LIST,
    PRIMITIVE_TYPE_LINE_LIST,
    PRIMITIVE_TYPE_LINE_STRIP,
    PRIMITIVE_TYPE_TRIANGLE_LIST,
    PRIMITIVE_TYPE_TRIANGLE_STRIP
};

class Buffer;
class BufferDesc;
class InputElement;
class InputElementDesc;
class Shader;
class Sprite;
class SubResourceDesc;
class Texture;
class VertexStreamDesc;
struct SoundInfo;

class Renderer {
public:
    static std::shared_ptr<Buffer> createBuffer(const BufferDesc& desc, const SubResourceDesc* data = nullptr);
    static std::shared_ptr<InputElement> createInputLayout(const InputElementDesc* layout, unsigned numElements, ID3D10Blob* compile);
    static void setVertexBuffer(const VertexStreamDesc* stream, unsigned numStream = 1, unsigned start = 0);
    static void setIndexBuffer(std::shared_ptr<Buffer> buffer, unsigned offset = 0);
    static void setInputLayout(std::shared_ptr<InputElement> layout);
    static void setPrimitive(PrimitiveType primitive);

    static ID3D11VertexShader* getVertexShader(const char* fileName, const char* funcName);
    static ID3D11PixelShader* getPixelShader(const char* fileName, const char* funcName);
    static std::shared_ptr<Texture> getTexture(const char* fileName);
    static std::shared_ptr<SoundInfo> getSound(const char* fileName);

    static void draw(unsigned numVertex, unsigned start = 0);
    static void drawIndexed(unsigned numIndices, unsigned startIndex = 0, int startVertex = 0);
    static void drawNumber(int number, const Vector2& position, bool isRightAlignment = false);
    static void clear();

private:
    static D3D11_PRIMITIVE_TOPOLOGY toPrimitiveMode(PrimitiveType primitive);

private:
    static std::unordered_map<const char*, ID3D11VertexShader*> mVertexShaders;
    static std::unordered_map<const char*, ID3D11PixelShader*> mPixelShaders;
    static std::unordered_map<const char*, std::shared_ptr<Texture>> mTextures;
    static std::unordered_map<const char*, std::shared_ptr<SoundInfo>> mSounds;
};

