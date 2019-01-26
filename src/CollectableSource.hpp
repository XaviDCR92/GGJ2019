#pragma once

#include "SpaceEntity.hpp"
#include "MultiSpriteEntity.hpp"

class CollectableSource : public SpaceEntity, public CompositeSpriteEntity
{
public:
    CollectableSource(GsSprite& spr, const Camera& cam);
    virtual void Update(void* const data) override;
    virtual void render(const Camera& cam);

private:

    int mHealth, mConsuptionSpeed, mMaxHealth;
    const int mSpriteAmount;
    int mSpriteOffsets[5];
};