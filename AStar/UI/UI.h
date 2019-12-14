#pragma once

#include <list>
#include <memory>

enum class UIState {
    ACTIVE,
    CLOSING
};

class Sprite;

class UI {
public:
    UI();
    virtual ~UI();
    virtual void update() = 0;
    void close();
    void addSprite(std::shared_ptr<Sprite> add);
    UIState getState() const;

private:
    std::list<std::shared_ptr<Sprite>> mSprites;
    UIState mState;
};
