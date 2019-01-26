#include "Planet.hpp"
#include "GlobalData.h"
#include "Gfx.h"

Planet::Planet(GsSprite& spr, const Camera& cam) : SpaceEntity(spr, cam),
    mConsumerAmount(0), mHealth(3000), mConsuptionSpeed(3)
{
    setActive(true);
    mPosition = Vector2(40, 20);
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
    {
        setActive(false);
    }
}
