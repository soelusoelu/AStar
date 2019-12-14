#include "Tile.h"
#include "../Component/SpriteComponent.h"

Tile::Tile(int index, int value) :
    Actor(),
    sprite(new SpriteComponent(this, "block.png", 0.5f)),
    state(TileState::NONE),
    adjacent(0),
    parent(nullptr),
    c(0),
    h(0),
    s(0),
    isOpened(false),
    isClosed(false),
    index(index)
{
    switch (value) {
    case static_cast<int>(TileState::ROAD) :
        sprite->setUV(0.f, 0.f, 0.25f, 1.f);
        state = TileState::ROAD;
        break;
    case static_cast<int>(TileState::BLOCK) :
        sprite->setUV(0.25f, 0.f, 0.5f, 1.f);
        state = TileState::BLOCK;
        break;
    case static_cast<int>(TileState::START) :
        sprite->setUV(0.5f, 0.f, 0.75f, 1.f);
        state = TileState::START;
        break;
    case static_cast<int>(TileState::GOAL) :
        sprite->setUV(0.75f, 0.f, 1.f, 1.f);
        state = TileState::GOAL;
        break;
    }
}

Tile::~Tile() = default;

void Tile::updateActor() {
}

void Tile::drawActor() const {
}

TileState Tile::getState() const {
    return state;
}

void Tile::computeScore() {
    s = c + h;
}

const int Tile::GRID_SIZE = 64;
