#pragma once

#include "../Utility/IManager.h"
#include <list>
#include <memory>

class UI;

class UIManager : public IManager<UI> {
public:
    UIManager();
    ~UIManager();
    virtual void update() override;
    virtual void draw() const override;
    void add(UI* add);
    virtual void remove() override;
    virtual void clear() override;

private:
    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

private:
    std::list<std::unique_ptr<UI>> mUIStack;
};
