#pragma once

#include "Vector2.hpp"
#include "Gfx.h"
#include "Camera.hpp"
#include <fixmath.h>

class Camera;

class SpaceEntity
{
public:
    SpaceEntity(GsSprite& spr, const Camera& cam);
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
    const Camera& mCamera;
    size_t mArrayIdx;
};
