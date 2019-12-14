#include "Actor.h"
#include "ActorManager.h"
#include "ComponentManagementOfActor.h"
#include "Transform2D.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"

Actor::Actor(const char* tag) :
    mComponentManager(std::make_shared<ComponentManagementOfActor>()),
    mTransform(std::make_shared<Transform2D>()),
    mDestroyTimer(nullptr),
    mState(ActorState::ACTIVE),
    mTag(tag) {
    ActorManager::add(this);
}

Actor::~Actor() = default;

void Actor::update() {
    mComponentManager->start();
    if (mState == ActorState::ACTIVE) {
        computeWorldTransform();

        mComponentManager->update();
        updateActor();

        computeWorldTransform();

        destroyTimer();
    }
}

void Actor::computeWorldTransform() {
    auto s = mComponentManager->getComponent<SpriteComponent>();
    if (!s) {
        return;
    }
    if (mTransform->computeWorldTransform(s->getCurrentTextureSize(), s->getPivot(), s->getDepth())) {
        s->setWorld(mTransform->getWorldTransform());
        mComponentManager->onUpdateWorldTransform();
    }
}

void Actor::destroy(Actor * actor) {
    actor->mState = ActorState::DEAD;
}

void Actor::destroy(std::shared_ptr<Actor> actor) {
    actor->mState = ActorState::DEAD;
}

void Actor::destroy(Actor * actor, float sec) {
    if (actor->mDestroyTimer) {
        return;
    }
    actor->mDestroyTimer = std::make_unique<Time>(sec);
}

void Actor::destroy(std::shared_ptr<Actor> actor, float sec) {
    if (actor->mDestroyTimer) {
        return;
    }
    actor->mDestroyTimer = std::make_unique<Time>(sec);
}

std::shared_ptr<ComponentManagementOfActor> Actor::getComponentManager() const {
    return mComponentManager;
}

std::shared_ptr<Transform2D> Actor::getTransform() const {
    return mTransform;
}

ActorState Actor::getState() const {
    return mState;
}

const char* Actor::getTag() const {
    return mTag;
}

void Actor::destroyTimer() {
    if (!mDestroyTimer) {
        return;
    }
    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        mState = ActorState::DEAD;
    }
}
