#include "SceneBase.h"
#include <memory>

class SceneManager {
public:
    SceneManager();
    ~SceneManager();
    void update();
    void draw() const;

private:
    void change(Scene next);

private:
    std::shared_ptr<SceneBase> mCurrentScene;
};
