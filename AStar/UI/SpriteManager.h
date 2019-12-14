#pragma once

#include "../Utility/IManager.h"
#include <memory>
#include <list>

class Sprite;

class SpriteManager : public IManager<Sprite> {
public:
    SpriteManager();
    ~SpriteManager();
    virtual void update() override;
    virtual void draw() const override;
    static void add(std::shared_ptr<Sprite> add);
    virtual void remove() override;
    virtual void clear() override;

private:
    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;
    void sortByZ(); //未実装

private:
    static std::list<std::shared_ptr<Sprite>> mSprites;
};

