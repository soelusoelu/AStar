#include "ActorManager.h"
#include "Actor.h"
#include <algorithm>
#include <iterator>

ActorManager::ActorManager() = default;

ActorManager::~ActorManager() = default;

void ActorManager::update() {
    mUpdatingActors = true;
    for (auto&& actor : mActors) {
        actor->update();
    }
    mUpdatingActors = false;

    movePendingToMain();

    remove();
}

void ActorManager::draw() const {
    for (const auto& actor : mActors) {
        actor->drawActor();
    }
}

void ActorManager::add(Actor * add) {
    if (mUpdatingActors) {
        mPendingActors.emplace_back(add);
    } else {
        mActors.emplace_back(add);
    }
}

void ActorManager::remove() {
    auto itr = mActors.begin();
    while (itr != mActors.end()) {
        if ((*itr)->getState() == ActorState::DEAD) {
            itr = mActors.erase(itr);
        } else {
            ++itr;
        }
    }
}

void ActorManager::clear() {
    mPendingActors.clear();
    mActors.clear();
}

void ActorManager::movePendingToMain() {
    if (mPendingActors.empty()) {
        return;
    }
    std::copy(mPendingActors.begin(), mPendingActors.end(), std::back_inserter(mActors));
    mPendingActors.clear();
}

std::list<std::shared_ptr<Actor>> ActorManager::mActors;
std::list<std::shared_ptr<Actor>> ActorManager::mPendingActors;
bool ActorManager::mUpdatingActors = false;