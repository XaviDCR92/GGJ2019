#include "SpaceEntity.hpp"

SpaceEntity::SpaceEntity() :
    mActive(false)
{
}

bool SpaceEntity::IsColliding(const SpaceEntity& otherEntity) const
{
    return (mPosition - otherEntity.mPosition).DistanceSqrt() < (mRadius+otherEntity.mRadius)*(mRadius+otherEntity.mRadius);
}

bool SpaceEntity::isActive(void)
{
    return mActive;
}

void SpaceEntity::setActive(const bool state)
{
    mActive = state;
}
