#pragma once

#include "SpaceEntity.hpp"

class Camera;

class Planet : public SpaceEntity
{
public:

    Planet(GsSprite& spr, const Camera& cam);
    virtual void Update(void* const data) override;

private:

    int mConsumerAmount, mHealth, mConsuptionSpeed;

};
