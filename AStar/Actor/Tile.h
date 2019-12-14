#pragma once

#include "Actor.h"
#include <memory>
#include <vector>

class SpriteComponent;

enum class TileState {
    ROAD = 0,
    BLOCK = 1,
    START = 2,
    GOAL = 3,

    NONE
};

struct Tile : public Actor {
    Tile(int index, int value);
    ~Tile();
    virtual void updateActor() override;
    virtual void drawActor() const override;
    TileState getState() const;
    void computeScore();

    SpriteComponent* sprite;
    TileState state;
    std::vector<Tile*> adjacent; //隣接タイル
    Tile* parent;
    int c; //実コスト
    int h; //推定コスト
    int s; //スコア
    bool isOpened;
    bool isClosed;
    int index;
    static const int GRID_SIZE;
};

