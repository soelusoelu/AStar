#pragma once

#include "SceneBase.h"
#include "../Device/Sound.h"
#include <memory>

class Title : public SceneBase {
public:
    Title();
    ~Title();
    virtual void updateScene() override;
    virtual void drawScene() const override;

private:
    std::shared_ptr<SoundInfo> mSound;
};
