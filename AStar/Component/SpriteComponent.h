#pragma once

#include "Component.h"
#include "../UI/Sprite.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Sprite;

class SpriteComponent : public Component {
public:
    SpriteComponent(Actor* owner, const char* fileName, float z);
    ~SpriteComponent();
    virtual void update() override;
    std::shared_ptr<Sprite> getSprite() const;

    //描画優先順位(0〜1、0が手前)
    void setPrimary(float z);
    float getDepth() const;
    //色味、たぶん0〜1
    void setColor(const Vector3& color);
    void setColor(float r, float g, float b);
    //不透明度(0〜1、1が不透明, 0が透明)
    void setAlpha(float alpha);
    Vector4 getColor() const;
    //切り取り範囲(left, top, right, bottom, 0〜1)
    void setUV(float l, float t, float r, float b);
    Vector4 getUV() const;
    //回転ピボット位置
    void setPivot(const Vector2& pivot);
    Vector2 getPivot() const;
    //テクスチャサイズの取得
    Vector2 getTextureSize() const;
    //テクスチャの現在のサイズを取得
    Vector2 getCurrentTextureSize() const;
    //スクリーン表示上のサイズの取得
    Vector2 getScreenTextureSize() const;
    //状態管理
    void inactive();
    SpriteState getState() const;
    //World行列
    void setWorld(const Matrix4& world);
    Matrix4 getWorld() const;
    //テクスチャ
    void setTexture(const char* fileName);
    std::shared_ptr<Texture> texture() const;
    //シェーダーの取得
    std::shared_ptr<Shader> shader() const;
    //ファイル名の取得
    const char* fileName() const;

private:
    std::shared_ptr<Sprite> mSprite;
};
