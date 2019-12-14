#pragma once

#include "SceneBase.h"
#include "../UI/Sprite.h"
#include <memory>

enum class GameState {
    PLAY,
    PAUSED,
    FADE,
    RESULT,
    QUIT
};

class ActorManager;

class GamePlay : public SceneBase, public std::enable_shared_from_this<GamePlay> {
public:
    GamePlay();
    ~GamePlay();
    virtual void updateScene() override;
    virtual void drawScene() const override;

    GameState getState() const;
    void setState(GameState state);

private:
    std::shared_ptr<ActorManager> mActorManager;
    GameState mState;
};
