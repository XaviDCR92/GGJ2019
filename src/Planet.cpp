#include "Planet.hpp"
#include "GlobalData.h"

Planet(GsSprite& spr) : public SpaceEntity(spr)
    : mConsumerAmount(0), mHealth(3000), mConsuptionSpeed(3)
{
    mPosition = Vector2(200, 200);
}

void Planet::Update(void* const data)
{
    GlobalData* gData = static_cast<GlobalData*>(data);
    mConsumerAmount = 0;

    if(gData)
    {
        if(ArrayManager<Player>* players = gData->Players)
        {
            for(int i = 0; i < players.mSize; i++)
            {
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
    }

    mHealth -= mConsumerAmount*mConsuptionSPeed;
    if(mHealth <= 0)
        IsActive = false;
}