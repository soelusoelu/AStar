#include "Main.h"
#include "Scene/SceneManager.h"

Main::Main() :
    mScene(std::make_unique<SceneManager>()) {
}

Main::~Main() {
}

void Main::update() {
    mScene->update();
}

void Main::draw() const {
    mScene->draw();
}
