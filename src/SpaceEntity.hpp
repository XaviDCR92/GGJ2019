#pragma once

#include "Vector2.hpp"
#include <fixmath.h>

class SpaceEntity
{
public:
    SpaceEntity();
    virtual void Update(void* const) = 0;
    bool isActive(void);
    void setActive(const bool state);
    bool IsColliding(const SpaceEntity& otherEntity) const;

protected:
    bool mActive;
    Fix16 mRadius;
    Vector2 mPosition;
};
