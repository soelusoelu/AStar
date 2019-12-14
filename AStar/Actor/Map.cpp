#include "Map.h"
#include "Tile.h"
#include "Transform2D.h"
#include "../Component/SpriteComponent.h"
#include "../Device/CSVReader.h"
#include "../UI/Sprite.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"
#include <algorithm>
#include <list>

Map::Map(const char* fileName) :
    Actor(),
    mMap(CSVReader::load(fileName)),
    mFileName(fileName),
    mTiles(0),
    mWidth(CSVReader::getWidth()),
    mHeight(CSVReader::getHeight()),
    mNumTiles(mWidth* mHeight),
    mStartIndex(0),
    mGoalIndex(0),
    mMoveType(MoveType::CROSS_AND_DIAGONAL) {

    initialize();
    setAdjacentTiles();
    searchRoute();
}

Map::~Map() = default;

void Map::updateActor() {
    changeMoveType();
    changeMap();
}

void Map::drawActor() const {
}

void Map::initialize() {
    mTiles.reserve(mNumTiles);

    for (size_t i = 0; i < mNumTiles; i++) {
        auto value = mMap[i];
        auto tile = new Tile(i, value);
        tile->getTransform()->setPosition(Vector2(
            i % mWidth * Tile::GRID_SIZE,
            i / mWidth * Tile::GRID_SIZE
        ));
        mTiles.emplace_back(tile);

        if (value == static_cast<int>(TileState::START)) {
            mStartIndex = i;
        } else if (value == static_cast<int>(TileState::GOAL)) {
            mGoalIndex = i;
        }
    }
}

void Map::setAdjacentTiles() {
    for (auto&& tile : mTiles) {
        tile->adjacent.clear();
    }
    //�אڃ^�C�����Z�b�g
    for (size_t i = 0; i < mNumTiles; i++) {
        if (i > mWidth - 1) { //��
            mTiles[i]->adjacent.emplace_back(mTiles[i - mWidth]);
        }
        if (i < mNumTiles - mWidth) { //��
            mTiles[i]->adjacent.emplace_back(mTiles[i + mWidth]);
        }
        if (i % mWidth > 0) { //��
            mTiles[i]->adjacent.emplace_back(mTiles[i - 1]);
        }
        if (i % mWidth < mWidth - 1) { //�E
            mTiles[i]->adjacent.emplace_back(mTiles[i + 1]);
        }

        if (mMoveType == MoveType::CROSS_AND_DIAGONAL) {
            if (i > mWidth - 1) { //��
                if (i % mWidth > 0) { //����
                    mTiles[i]->adjacent.emplace_back(mTiles[i - mWidth - 1]);
                }
                if (i % mWidth < mWidth - 1) { //�E��
                    mTiles[i]->adjacent.emplace_back(mTiles[i - mWidth + 1]);
                }
            }
            if (i < mNumTiles - mWidth) { //��
                if (i % mWidth > 0) { //����
                    mTiles[i]->adjacent.emplace_back(mTiles[i + mWidth - 1]);
                }
                if (i % mWidth < mWidth - 1) { //�E��
                    mTiles[i]->adjacent.emplace_back(mTiles[i + mWidth + 1]);
                }
            }
        }
    }
}

void Map::searchRoute() {
    //����
    initializeTiles();

    auto current = mTiles[mStartIndex];
    auto goal = mTiles[mGoalIndex];

    current->isClosed = true;
    std::list<Tile*> openList;

    //�����J�n
    do {
        for (auto&& neighbor : current->adjacent) {
            if (neighbor->state == TileState::BLOCK) {
                continue;
            }
            if (!neighbor->isClosed) {
                if (!neighbor->isOpened) {
                    neighbor->parent = current;
                    neighbor->h = computeHeuristicCost(neighbor->index, goal->index);
                    neighbor->c = current->c + 1;
                    neighbor->computeScore();
                    openList.emplace_back(neighbor);
                    neighbor->isOpened = true;
                } else {
                    int c = current->c + 1;
                    if (c < neighbor->c) {
                        neighbor->c = c;
                        neighbor->parent = current;
                        neighbor->computeScore();
                    }
                }
            }
        }
        if (openList.empty()) {
            break;
        }
        //openList�̒�����X�R�A����ԏ��������T��
        auto itr = std::min_element(openList.begin(), openList.end(), [](Tile* a, Tile* b) {
            return a->s < b->s;
        });
        current = (*itr);
        openList.erase(itr);
        current->isOpened = false;
        current->isClosed = true;
    } while (current != goal);

    //�ړ��o�H��F�t��
    while (current) {
        current->sprite->setColor(1.f, 0.f, 0.f);
        current = current->parent;
    }
}

void Map::initializeTiles() {
    //�S�^�C���̏�����
    for (auto&& tile : mTiles) {
        tile->c = 0;
        tile->h = 0;
        tile->s = 0;
        tile->isOpened = false;
        tile->isClosed = false;
        tile->parent = nullptr;
        tile->sprite->setColor(1.f, 1.f, 1.f);
    }
}


int Map::computeHeuristicCost(int tileIndex, int goalIndex) {
    int tx = goalIndex % mWidth;
    int ty = goalIndex / mWidth;
    int dx = Math::abs(tx - tileIndex % mWidth);
    int dy = Math::abs(ty - tileIndex / mWidth);

    if (mMoveType == MoveType::CROSS_AND_DIAGONAL) {
        return Math::Max<int>(dx, dy);
    } else if (mMoveType == MoveType::CROSS) {
        return dx + dy;
    }
}

void Map::changeMoveType() {
    if (Input::getKeyDown(KeyCode::Space)) {
        mMoveType = (mMoveType == MoveType::CROSS) ? MoveType::CROSS_AND_DIAGONAL : MoveType::CROSS;
    }
    setAdjacentTiles();
    searchRoute();
}

void Map::changeMap() {
    if (!(Input::getKeyDown(KeyCode::Alpha1) || (Input::getKeyDown(KeyCode::Alpha2)))) {
        return;
    }
    const char* fileName = "";
    if (Input::getKeyDown(KeyCode::Alpha1)) {
        fileName = "map1.csv";
    } else if (Input::getKeyDown(KeyCode::Alpha2)) {
        fileName = "map2.csv";
    }
    //���ʂ͂����Ȃ�
    if (mFileName == fileName) {
        return;
    }
    mFileName = fileName;
    mMap = CSVReader::load(mFileName);
    mWidth = CSVReader::getWidth();
    mHeight = CSVReader::getHeight();
    mNumTiles = mWidth * mHeight;
    for (auto&& tile : mTiles) {
        Actor::destroy(tile);
    }
    mTiles.clear();
    initialize();
}
