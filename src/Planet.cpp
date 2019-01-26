#include "Planet.hpp"
#include "GlobalData.h"
#include "Gfx.h"

Planet::Planet(GsSprite& spr, const Camera& cam) : SpaceEntity(spr),
    mConsumerAmount(0), mHealth(3000), mConsuptionSpeed(3), mMaxHealth(4000)
{
    setActive(true);
    mPosition = Vector2(40, 20);
    mActive = true;
}

void Planet::Update(void* const data)
{
    GlobalData* gData = static_cast<GlobalData*>(data);
    mConsumerAmount = 0;

    if(gData)
    {
        ArrayManager<Player>& players = gData->Players;

        for (size_t i = 0; i < players.count(); i++)
        {
            Player& player = *players.get(i);

            if(player.isActive())
            {
                if(IsColliding(player))
                {
                    mConsumerAmount++;
                    break;
                }
            }
        }
    }

    mHealth -= mConsumerAmount*mConsuptionSpeed;
    if(mHealth <= 0)
        setActive(false);
}

void Planet::render(const Camera& cam)
{
    SetSpriteOriginOnce(mSpr.u, mSpr.v);

    int divisor = mMaxHealth / 6;
    int idx = mHealth / divisor;

    int offset = 0;
    int adder = 128;
    for(int i = 0; i < idx; i++)
    {
        offset += adder;
        adder /= 2;
    }

    unsigned char u, v;
    GetSpriteOrigin(u, v);
    //mSpr.u = u + offset;
    //mSpr.v = v;
    mSpr.w = 64; // adder
    mSpr.h = 64; // adder

    SpaceEntity::render(cam);
}
