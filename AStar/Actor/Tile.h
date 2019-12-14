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
    std::vector<Tile*> adjacent; //�אڃ^�C��
    Tile* parent;
    int c; //���R�X�g
    int h; //����R�X�g
    int s; //�X�R�A
    bool isOpened;
    bool isClosed;
    int index;
    static const int GRID_SIZE;
};

