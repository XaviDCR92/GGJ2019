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
    mEarthSpr.x = x;
    mEarthSpr.y = y;

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