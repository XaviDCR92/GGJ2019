#pragma once

#include "Gfx.h"
#include "Camera.hpp"

class ResourceBar
{
public:
    ResourceBar(GsSprite& spr);

    void render(const Camera& camera, short x, short y);

    int mStacks;
    int mMaxStacks;
    const short mSpriteWidth[4];

private:

    GsSprite& mSpr;
};