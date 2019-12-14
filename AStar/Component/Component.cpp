#include "Component.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"

Component::Component(Actor* owner, int updateOrder) :
    mOwner(owner),
    mUpdateOrder(updateOrder) {
    mOwner->getComponentManager()->addComponent(this);
}

Component::~Component() = default;

int Component::getUpdateOrder() const {
    return mUpdateOrder;
}

Actor* Component::getOwner() const {
    return mOwner;
}
