#include "SpaceEntity.hpp"
#include "Gfx.h"
#include <stdio.h>

SpaceEntity::SpaceEntity(GsSprite& spr) :
    mActive(false),
    mSpr(spr),
    mArrayIdx(0)
{
}

bool SpaceEntity::IsColliding(const SpaceEntity& otherEntity) const
{
    printf("Distance: %d\n", fix16_to_int((mPosition - otherEntity.mPosition).Distance()));
    return (mPosition - otherEntity.mPosition).DistanceSqrt() < (mRadius+otherEntity.mRadius)*(mRadius+otherEntity.mRadius);
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
