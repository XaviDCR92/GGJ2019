#pragma once

#include "SpaceEntity.hpp"

class Planet : public SpaceEntity
{
public:

    Planet(GsSprite& spr);
    virtual void Update(void* const data) override;

    virtual void render(void);

private:

    int mConsumerAmount, mHealth, mConsuptionSpeed;

};
