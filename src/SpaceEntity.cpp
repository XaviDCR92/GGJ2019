#include "SpaceEntity.hpp"

bool SpaceEntity::IsColliding(const SpaceEntity& otherEntity) const
{
    return (mPosition - otherEntity.mPosition).DistanceSqrt() < (mRadius+otherEntity.mRadius)*(mRadius+otherEntity.mRadius);
}