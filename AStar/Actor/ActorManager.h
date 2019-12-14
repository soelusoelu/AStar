#pragma once

#include "../Utility/IManager.h"
#include "../Utility/Singleton.h"
#include <memory>
#include <list>

class Actor;

class ActorManager : public IManager<Actor> {
public:
    ActorManager();
    ~ActorManager();
    virtual void update() override;
    virtual void draw() const override;
    static void add(Actor* add);
    virtual void remove() override;
    virtual void clear() override;

    //一番最初に見つかったActorの取得
    template<typename T>
    std::shared_ptr<T> getActor() const {
        std::shared_ptr<T> actor = nullptr;
        for (const auto& a : mActors) {
            actor = std::dynamic_pointer_cast<T>(a);
            if (actor) {
                return actor;
            }
        }
        for (const auto& a : mPendingActors) {
            actor = std::dynamic_pointer_cast<T>(a);
            if (actor) {
                break;
            }
        }
        //最後まで見つからなければnullptrを返す
        return actor;
    }

private:
    void movePendingToMain();

    ActorManager(const ActorManager&) = delete;
    ActorManager& operator=(const ActorManager&) = delete;

private:
    static std::list<std::shared_ptr<Actor>> mActors;
    static std::list<std::shared_ptr<Actor>> mPendingActors;
    static bool mUpdatingActors;
};

