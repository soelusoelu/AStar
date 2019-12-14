#include "SceneBase.h"
#include "../UI/SpriteManager.h"
#include "../UI/UIManager.h"

SceneBase::SceneBase() :
    mUIManager(std::make_unique<UIManager>()),
    mSpriteManager(std::make_unique<SpriteManager>()),
    mNext(Scene::NONE) {
}

SceneBase::~SceneBase() {
    mUIManager->clear();
    mSpriteManager->clear();
}

void SceneBase::update() {
    updateScene();
    mUIManager->update();
    mSpriteManager->update();
}

void SceneBase::draw() {
    drawScene();
    mSpriteManager->draw();
}

void SceneBase::next(Scene next) {
    mNext = next;
}

Scene SceneBase::getNextScene() const {
    return mNext;
}
