#pragma once

#include "SpaceEntity.hpp"
#include "MultiSpriteEntity.hpp"

class Camera;

class Planet : public SpaceEntity, public CompositeSpriteEntity
{
public:

    Planet();
    Planet(const unsigned int health);
    virtual void Update(GlobalData& data) override;
    virtual void render(const Camera& cam);

private:
    const unsigned int mMaxHealth, mConsumptionSpeed;
    unsigned int mConsumerAmount;
    const size_t mSpriteAmount;
    const struct
    {
        short d;
        unsigned char u;
        unsigned char v;
    } mSpriteOffsets[5];
    bool mFlicker;

};

void PlanetInit(void);
