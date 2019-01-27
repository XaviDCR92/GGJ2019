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

    unsigned int mHealth, mConsumptionSpeed, mMaxHealth;
    const int mSpriteAmount;
    const struct
    {
        short d;
        unsigned char u;
        unsigned char v;
    } mSpriteOffsets[5];
};

void ResourcesInit(void);
