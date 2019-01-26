#include "Planet.hpp"
#include "GlobalData.h"
#include "Gfx.h"

Planet::Planet(GsSprite& spr, const Camera& cam) : SpaceEntity(spr), CompositeSpriteEntity(spr),
    mConsumerAmount(0), mHealth(4000), mConsuptionSpeed(5), mMaxHealth(4000), mSpriteAmount(5)
{
    setActive(true);
    mPosition = Vector2(110, 0);
    mActive = true;

    mSpriteOffsets[0] = 64;
    mSpriteOffsets[1] = 48;
    mSpriteOffsets[2] = 32;
    mSpriteOffsets[3] = 24;
    mSpriteOffsets[4] = 16;
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
    int divisor = mMaxHealth /mSpriteAmount;
    int safe_health = mHealth - 1;
    int idx = safe_health / divisor;
    idx = mSpriteAmount - idx;

    unsigned char u, v;
    GetSpriteOrigin(u, v);
    mSpr.u = u;
    mSpr.v = v;
    int i;
    for(i = 0; i < idx; i++)
        mSpr.u += mSpriteOffsets[i];
    mSpr.w = mSpriteOffsets[i];
    mSpr.h = mSpriteOffsets[i];
    
    SpaceEntity::render(cam);
}
