#pragma once

#include "Vector2.hpp"

class SpaceEntity
{
public:

    bool IsColliding(const SpaceEntity& otherEntity) const;

protected:
    Fix16 mRadius;
    Vector2 mPosition;
};