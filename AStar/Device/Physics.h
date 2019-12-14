#pragma once

#include <vector>

class Actor;
class Collider;

class Physics {
public:
    Physics();
    ~Physics();
    //ボックスコンポーネントの追加・削除
    static void add(Collider* circle);
    static void remove(Collider* circle);
    //全削除
    static void clear();
    //総当たり判定
    static void sweepAndPrune();

private:
    static std::vector<Collider*> mColliders;
};
