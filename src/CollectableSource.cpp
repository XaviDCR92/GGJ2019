#include "CollectableSource.hpp"
#include "GlobalData.h"
#include "ArrayManager.hpp"
#include "Player.hpp"
#include "Gfx.h"

CollectableSource::CollectableSource(GsSprite& spr):
    SpaceEntity(spr), CompositeSpriteEntity(spr),
    mHealth(4000),
    mConsumptionSpeed(5),
    mMaxHealth(4000),
    mSpriteAmount(ARRAY_SIZE(mSpriteOffsets)),
    mSpriteOffsets {64, 48, 32, 24, 16}
{
    setActive(true);
    mPosition = Vector2(100, 100);
}

void CollectableSource::Update(GlobalData& gData)
{
    ArrayManager<Player>& players = gData.Players;

    for (size_t i = 0; i < players.count(); i++)
    {
        Player& player = *players.get(i);

        if(player.isActive())
        {
            if(IsColliding(player, gData.camera))
            {
                mHealth -= mConsumptionSpeed;
                printf("mHealth = %d\n", mHealth);

                // Player needs get resources here

                if(mHealth <= 0)
                    break;
            }
        }
    }
}
void CollectableSource::render(const Camera& cam)
{
    #if 0
    const int divisor = mMaxHealth /mSpriteAmount;
    const int safe_health = mHealth - 1;
    int idx = safe_health / divisor;
    idx = mSpriteAmount - idx;

    //~ unsigned char u, v;
    //~ GetSpriteOrigin(u, v);
    //~ mSpr.u = u;
    //~ mSpr.v = v;
    int i;
    //~ for(i = 0; i < idx; i++)
        //~ mSpr.u += mSpriteOffsets[i];
    //~ mSpr.w = 96;
    //~ mSpr.h = 96;
    #endif

    SpaceEntity::render(cam);
}
