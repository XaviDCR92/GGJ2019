#pragma once

#include "Vector2.hpp"
#include <fixmath.h>

class SpaceEntity
{
public:

    bool IsColliding(const SpaceEntity& otherEntity) const;

protected:
    Fix16 mRadius;
    Vector2 mPosition;
};
