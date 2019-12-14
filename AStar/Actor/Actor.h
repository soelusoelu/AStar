#pragma once

#include "../Utility/Math.h"
#include <memory>

enum class ActorState {
    ACTIVE,
    DEAD
};

class ComponentManagementOfActor;
class Transform2D;
class Time;

class Actor {
public:
    Actor(const char* tag = "");
    virtual ~Actor();

    //すべての更新
    void update();
    //アクター固有の更新
    virtual void updateActor() = 0;
    //描画
    virtual void drawActor() const = 0;

    //ワールド行列の更新
    void computeWorldTransform();

    //アクター削除
    static void destroy(Actor* actor);
    static void destroy(std::shared_ptr<Actor> actor);
    static void destroy(Actor* actor, float sec);
    static void destroy(std::shared_ptr<Actor> actor, float sec);

    //ゲッター、セッター
    std::shared_ptr<ComponentManagementOfActor> getComponentManager() const;
    std::shared_ptr<Transform2D> getTransform() const;
    ActorState getState() const;
    const char* getTag() const;

private:
    void destroyTimer();

private:
    std::shared_ptr<ComponentManagementOfActor> mComponentManager;
    std::shared_ptr<Transform2D> mTransform;
    std::unique_ptr<Time> mDestroyTimer;
    ActorState mState;
    const char* mTag;
};

