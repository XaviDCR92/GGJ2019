#include "SpaceEntity.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>

SpaceEntity::SpaceEntity(GsSprite& spr) :
    mActive(false),
    mSpr(spr),
    mArrayIdx(0),
    mRadius(fix16_from_int(32)),
    mHealth(0)
{
}

bool SpaceEntity::isCollidingWith(const SpaceEntity& other) const
{
    unsigned int x = abs(fix16_to_int(getPosition().X.value) - fix16_to_int(other.getPosition().X.value));
    x *= x;

    unsigned int y = abs(fix16_to_int(getPosition().Y.value) - fix16_to_int(other.getPosition().Y.value));
    y *= y;

    const int distance = x + y;
    int radius = fix16_to_int(mRadius);
    radius *= radius;

    return distance < radius;
}

bool SpaceEntity::isActive(void) const
{
    return mActive;
}

void SpaceEntity::setActive(const bool state)
{
    mActive = state;
}

void SpaceEntity::render(const Camera& camera)
{
    short x, y;

    GetRenderPosition(x, y);

    camera.getPosition(x, y);

    mSpr.x = x;
    mSpr.y = y;

    GfxSortSprite(&mSpr);
}

void SpaceEntity::GetRenderPosition(short& outX, short &outY) const
{
    outX = fix16_to_int(mPosition.X.value) - (mSpr.w >> 1);
    outY = fix16_to_int(mPosition.Y.value) - (mSpr.h >> 1);
}

Vector2 SpaceEntity::getPosition(void) const
{
    return mPosition;
}
