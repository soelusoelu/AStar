#pragma once

#include <memory>

class SceneManager;

class Main {
public:
    Main();
    ~Main();
    void update();
    void draw() const;

private:
    std::unique_ptr<SceneManager> mScene;
};

