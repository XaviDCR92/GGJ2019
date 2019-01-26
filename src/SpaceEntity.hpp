#pragma once

#include "Vector2.hpp"
#include "Gfx.h"
#include <fixmath.h>

class SpaceEntity
{
public:
    explicit SpaceEntity(GsSprite& spr);
    virtual void Update(void* const) = 0;
    bool isActive(void) const;
    void setActive(const bool state);
    bool IsColliding(const SpaceEntity& otherEntity) const;

protected:
    void render(void);
    void GetRenderPosition(short& outX, short &outY) const;

    bool mActive;
    Fix16 mRadius;
    Vector2 mPosition;
    GsSprite& mSpr;
};
