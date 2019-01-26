#pragma once

#include "SpaceEntity.hpp"
#include "MultiSpriteEntity.hpp"

class Camera;

class Planet : public SpaceEntity, public CompositeSpriteEntity
{
public:

    Planet(GsSprite& spr, const Camera& cam);
    virtual void Update(GlobalData& data) override;

    virtual void render(const Camera& cam);

private:

    int mConsumerAmount, mHealth, mConsuptionSpeed, mMaxHealth;
    const int mSpriteAmount = 5;
    int mSpriteOffsets[5];

};
