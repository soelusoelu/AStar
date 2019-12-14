#pragma once

#include "Actor.h"
#include <memory>
#include <vector>

class Tile;

enum class MoveType {
    CROSS, //ècâ°
    CROSS_AND_DIAGONAL //ècâ°éŒÇﬂ
};

class Map : public Actor {
public:
    Map(const char* fileName);
    ~Map();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    void initialize();
    void setAdjacentTiles();
    void searchRoute();
    void initializeTiles();
    int computeHeuristicCost(int tileIndex, int goalIndex);
    void changeMoveType();
    void changeMap();

private:
    std::vector<int> mMap;
    const char* mFileName;
    std::vector<Tile*> mTiles;
    size_t mWidth;
    size_t mHeight;
    size_t mNumTiles;
    int mStartIndex;
    int mGoalIndex;
    MoveType mMoveType;
};

