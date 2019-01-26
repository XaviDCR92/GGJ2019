#include "Planet.hpp"
#include "GlobalData.h"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include "Gfx.h"

Planet::Planet(GsSprite& spr, const Camera& cam) : SpaceEntity(spr), CompositeSpriteEntity(spr),
    mConsumerAmount(0), mHealth(4000), mConsuptionSpeed(20), mMaxHealth(4000)
{
    setActive(true);
    mPosition = Vector2(40, 20);
    mActive = true;

    mSpriteOffsets[0] = 64;
    mSpriteOffsets[1] = 48;
    mSpriteOffsets[2] = 32;
    mSpriteOffsets[3] = 24;
    mSpriteOffsets[4] = 16;
}

void Planet::Update(GlobalData& gData)
{
    mConsumerAmount = 0;

    ArrayManager<Player>& players = gData.Players;

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

    mHealth -= mConsumerAmount*mConsuptionSpeed;
    if(mHealth <= 0)
        setActive(false);
}

void Planet::render(const Camera& cam)
{
    //SetSpriteOriginOnce(mSpr.u, mSpr.v);

    int divisor = mMaxHealth /mSpriteAmount;
    int safe_health = mHealth - 1;
    int idx = safe_health / divisor;
    idx = mSpriteAmount - idx;

    unsigned char u, v;
    GetSpriteOrigin(u, v);
    mSpr.u = u;
    mSpr.v = v;
    //for(i = 0; i < idx; i++)
    //    mSpr.u += mSpriteOffsets[i];
    //mSpr.w = mSpriteOffsets[i];
    //mSpr.h = mSpriteOffsets[i];
    mSpr.w = 64;
    mSpr.h = 64;

    SpaceEntity::render(cam);
}
