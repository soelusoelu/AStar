#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class SpriteComponent;
class Time;

class AnimationComponent : public Component {
public:
    AnimationComponent(Actor* owner, float changeTimerSec, const Vector2& oneSpriteSize);
    ~AnimationComponent();
    virtual void start() override;
    virtual void update() override;
    void set(int verticalIndex);

private:
    void change();

private:
    std::unique_ptr<Time> mChangeTimer;
    std::shared_ptr<SpriteComponent> mSprite;
    Vector2 mSize;
    int mWidthCount;
    int mHeightCount;
    int mCurrentIndex;
    int mPreviousVerticalIndex;
    int mVerticalIndex;
};

