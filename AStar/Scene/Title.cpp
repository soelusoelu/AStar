#include "Title.h"
#include "../Device/Renderer.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

Title::Title() :
    SceneBase() {
    new Sprite("Title.png", 0.1f);
    mSound = Renderer::getSound("Title.wav");
    mSound->play(true);
}

Title::~Title() {
    mSound->stop();
}

void Title::updateScene() {
    if (Input::getKeyDown(KeyCode::Space)) {
        next(Scene::SCENE_SOUSA);
    }
}

void Title::drawScene() const {
}
