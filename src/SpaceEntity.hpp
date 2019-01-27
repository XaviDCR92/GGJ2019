#pragma once

#include "Vector2.hpp"
#include "Gfx.h"
#include "Camera.hpp"
#include "GlobalData.h"
#include <fixmath.h>
#include <stdint.h>
#include <stddef.h>

class SpaceEntity
{
public:
    SpaceEntity(GsSprite& spr);
    virtual void Update(GlobalData& gData) = 0;
    bool isActive(void) const;
    void setActive(const bool state);
    bool isCollidingWith(const SpaceEntity& other) const;

    virtual void render(const Camera& cam);
    Vector2 getPosition(void) const;
    Vector2 mPosition;

protected:
    void GetRenderPosition(short& outX, short &outY) const;

    bool mActive;
    GsSprite& mSpr;
    size_t mArrayIdx;
    Fix16 mRadius;
    unsigned int mHealth;
};
