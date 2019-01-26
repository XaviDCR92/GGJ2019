#include "Planet.hpp"
#include "GlobalData.h"

Planet::Planet(GsSprite& spr) : SpaceEntity(spr), 
    mConsumerAmount(0), mHealth(3000), mConsuptionSpeed(3)
{
    mPosition = Vector2(40, 20);
    mActive = true;
}

void Planet::Update(void* const data)
{
    GlobalData* gData = static_cast<GlobalData*>(data);
    mConsumerAmount = 0;

    if(gData)
    {
        if(ArrayManager<Player>* players = gData->Players)
        {
            for(unsigned i = 0; i < players->count(); i++)
            {
                if(Player* player = players->get(i))
                {
                    if(player->isActive())
                    {
                        if(IsColliding(*player))
                        {
                            mConsumerAmount++;
                            break;
                        }
                    }
                }
            }
        }
    }

    mHealth -= mConsumerAmount*mConsuptionSpeed;
    if(mHealth <= 0)
        mActive = false;
}

void Planet::render()
{


    SpaceEntity::render();
}