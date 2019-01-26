#pragma once

#include "SpaceEntity.hpp"

class Planet : public SpaceEntity
{
public:

    Planet(GsSprite& spr);
    virtual void Update(void* const data) override;

private:

    int mConsumerAmount, mHealth, mConsuptionSpeed;

};
