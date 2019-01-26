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
    void render(void);
    Vector2 getPosition(void) const;

Vector2 mPosition;

protected:
    void GetRenderPosition(short& outX, short &outY) const;

    bool mActive;
    Fix16 mRadius;
    
    GsSprite& mSpr;

    uint16_t mArrayIdx;
};
