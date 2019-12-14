#pragma once

#include "SceneBase.h"

class Sousa : public SceneBase {
public:
    Sousa();
    ~Sousa();
    virtual void updateScene() override;
    virtual void drawScene() const override;
};

