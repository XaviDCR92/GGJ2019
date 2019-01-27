#include "Earth.hpp"

static GsSprite earthSprite;

void EarthInit()
{
    GfxSpriteFromFile("DATA\\SPRITES\\EARTH.TIM", &earthSprite);
}

Earth::Earth() :
    Planet(1900),
    mEarthSpr(earthSprite),
    mHealthPerResource(800)
{
    mPosition = Vector2(100, 100);
}

void Earth::Update(GlobalData& data)
{
    Planet::Update(data);
}

void Earth::render(const Camera& cam)
{
    short x,y;
    GetRenderPosition(x,y);
    cam.getPosition(x, y);
    mEarthSpr.x = x - (mEarthSpr.w >> 2);
    mEarthSpr.y = y - (mEarthSpr.h >> 2);

    GfxSortSprite(&mEarthSpr);

    Planet::render(cam);
}

void Earth::DumpResources(int amount)
{
    mHealth += amount*mHealthPerResource;
    if(mHealth > mMaxHealth)
    {
        mHealth = mMaxHealth;
        // Victory condition goes here
        // ...
    }
}
