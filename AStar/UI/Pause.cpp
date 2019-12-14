#include "Pause.h"
#include "Sprite.h"
#include "../Scene/GamePlay.h"
#include "../UI/SpriteManager.h"
#include "../Utility/Input.h"
#include <list>

Pause::Pause(std::shared_ptr<GamePlay> game) :
    UI(),
    mGame(game) {
    if (auto g = mGame.lock()) {
        g->setState(GameState::PAUSED);
    }
    addSprite(std::make_shared<Sprite>("kuppa.png", 0.6f));
    addSprite(std::make_shared<Sprite>("cute_cat_illust_3737.png", 0.1f));
    addSprite(std::make_shared<Sprite>("menuBG.png", 0.9f));
}

Pause::~Pause() {
    if (auto g = mGame.lock()) {
        g->setState(GameState::PLAY);
    }
}

void Pause::update() {
    if (Input::getKeyDown(KeyCode::Alpha2)) {
        close();
    }
}
