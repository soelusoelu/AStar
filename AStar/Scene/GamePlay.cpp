#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/Map.h"
#include "../Device/Renderer.h"
#include <vector>

GamePlay::GamePlay() :
    SceneBase(),
    mActorManager(std::make_shared<ActorManager>()),
    mState(GameState::PLAY) {
    new Map("map1.csv");
}

GamePlay::~GamePlay() {
    mActorManager->clear();
    Renderer::clear();
}

void GamePlay::updateScene() {
    if (mState == GameState::PLAY) {
        mActorManager->update();
    }
}

void GamePlay::drawScene() const {
    mActorManager->draw();
}

GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}
