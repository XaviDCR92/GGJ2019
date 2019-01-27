#include "ResourceBar.h"

ResourceBar::ResourceBar(GsSprite& spr) : 
    mStacks(0),
    mMaxStacks(5),
    mSpriteWidth{ 0, 10, 21, 32 },
    mSpr(spr)
{

}

void ResourceBar::render(const Camera& camera, short x, short y)
{
    camera.getPosition(x, y);

    x += fix16_from_int(6);
    y += fix16_from_int(20);

    mSpr.x = x;
    mSpr.y = y;
    mSpr.w = mSpriteWidth[mStacks];
    mSpr.h = 6;

    GfxSortSprite(&mSpr);
}