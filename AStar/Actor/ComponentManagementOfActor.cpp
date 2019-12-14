#include "ComponentManagementOfActor.h"
#include "../Component/Component.h"

ComponentManagementOfActor::ComponentManagementOfActor() = default;

ComponentManagementOfActor::~ComponentManagementOfActor() {
    mStartComponents.clear();
    mComponents.clear();
}

void ComponentManagementOfActor::start() {
    for (auto&& comp : mStartComponents) {
        comp->start();

        int myOrder = comp->getUpdateOrder();
        auto itr = mComponents.begin();
        for (; itr != mComponents.end(); ++itr) {
            if (myOrder < (*itr)->getUpdateOrder()) {
                break;
            }
        }
        mComponents.insert(itr, comp);
    }
    mStartComponents.clear();
}

void ComponentManagementOfActor::update() {
    for (auto&& comp : mComponents) {
        comp->update();
    }
}

void ComponentManagementOfActor::addComponent(Component* component) {
    mStartComponents.emplace_back(component);
}

void ComponentManagementOfActor::onUpdateWorldTransform() {
    for (auto&& comp : mComponents) {
        comp->onUpdateWorldTransform();
    }
}
