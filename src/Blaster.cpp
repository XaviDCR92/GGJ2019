#include "Blaster.hpp"
#include "Gfx.h"
#include "SpaceEntity.hpp"
#include "GlobalData.h"

static GsSprite blasterSprite;

void BlasterInit(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\BLASTER.TIM", &blasterSprite);
}

Blaster::Blaster() : SpaceEntity(blasterSprite)
{
}

void Blaster::Update(GlobalData& data)
{
    if (isActive())
    {
    }
}

Blaster& Blaster::operator=(const Blaster& other)
{
    return *this = other;
}
