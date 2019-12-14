#pragma once

#include <random>

class Random {
public:
    static void init();
    static unsigned random();
    static int randomRange(int min, int max);
    static float randomRange(float min, float max);

private:
    static std::mt19937 mt;
};

