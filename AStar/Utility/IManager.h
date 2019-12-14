#pragma once

template<typename T>
class IManager {
public:
    virtual ~IManager() = default;
    virtual void update() = 0;
    virtual void draw() const = 0;
    //virtual void add(T* add) = 0;
    virtual void remove() = 0;
    virtual void clear() = 0;
};