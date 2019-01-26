#pragma once

#include "Gfx.h"

class CompositeSpriteEntity
{
public:

    CompositeSpriteEntity(GsSprite& spr) : mOriginSet(false), mStartU(spr.u), mStartV(spr.v)
    {}

    void SetSpriteOrigin(unsigned char startU, unsigned char startV);
    void GetSpriteOrigin(unsigned char& startU, unsigned char& startV) const;

private:

    bool mOriginSet;
    unsigned char mStartU, mStartV;
};