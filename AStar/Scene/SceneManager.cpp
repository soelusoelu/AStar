#include "SceneManager.h"
#include "GamePlay.h"
#include "Sousa.h"
#include "Title.h"

SceneManager::SceneManager() :
    mCurrentScene(std::make_shared<GamePlay>()) {
}

SceneManager::~SceneManager() = default;

void SceneManager::update() {
    mCurrentScene->update();

    if (mCurrentScene->getNextScene() != Scene::NONE) {
        change(mCurrentScene->getNextScene());
    }
}

void SceneManager::draw() const {
    mCurrentScene->draw();
}

void SceneManager::change(Scene next) {
    mCurrentScene.reset();
    if (next == Scene::SCENE_TITLE) {
        mCurrentScene = std::make_shared<Title>();
    } else if (next == Scene::SCENE_SOUSA) {
        mCurrentScene = std::make_shared<Sousa>();
    } else if (next == Scene::SCENE_GAME_PLAY) {
        mCurrentScene = std::make_shared<GamePlay>();
    }
}
