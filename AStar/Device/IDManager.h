#pragma once

#include <list>

enum class IDType {
    Mesh,
    Skeleton,
    Animation,
    Texture
};

class IDManager {
public:
    IDManager();
    ~IDManager() {};
    void push(unsigned id, IDType type);
    unsigned pop(IDType type);
    void clear();

private:
    std::list<unsigned> mMeshIDs;
    std::list<unsigned> mSkeletonIDs;
    std::list<unsigned> mAnimationIDs;
    std::list<unsigned> mTextureIDs;
};
