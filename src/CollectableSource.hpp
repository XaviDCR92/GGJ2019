#pragma once

#include "SpaceEntity.hpp"
#include "MultiSpriteEntity.hpp"
#include "GlobalData.h"

class CollectableSource : public SpaceEntity, public CompositeSpriteEntity
{
public:
    CollectableSource();
    virtual void Update(GlobalData& gData) override;
    virtual void render(const Camera& cam);

private:

    unsigned int mStacks;
    const int mSpriteAmount;
    const int mCollectionCounter;
    int mCurrentCollectionCounter;
    const int mFlickerCountStart;
    bool mFlicker;
    const struct
    {
        short d;
        unsigned char u;
        unsigned char v;
    } mSpriteOffsets[3];
};

void ResourcesInit(void);
