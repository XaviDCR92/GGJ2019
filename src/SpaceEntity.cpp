#include "SpaceEntity.hpp"
#include "Gfx.h"
#include <stdio.h>

SpaceEntity::SpaceEntity(GsSprite& spr) :
    mActive(false),
    mSpr(spr),
    mArrayIdx(0),
    mRadius(fix16_from_int(32))
{
}

bool SpaceEntity::IsColliding(const SpaceEntity& otherEntity) const
{
    return (mPosition - otherEntity.mPosition).Distance() < (mRadius+otherEntity.mRadius);
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
    outX = fix16_to_int(mPosition.X.value);
    outY = fix16_to_int(mPosition.Y.value);
}

Vector2 SpaceEntity::getPosition(void) const
{
    return mPosition;
}
