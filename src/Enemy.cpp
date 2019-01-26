#include "Enemy.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include "GlobalData.h"
#include <stdio.h>
#include <stdlib.h>

Enemy::Enemy(GsSprite& spr) :
    Ship(spr)
{
    mPosition = Vector2(10, 200);
    mMaxSpeed = 0x17FFE;
    mAccel = 0x400;
    mTurnRate = 0x1000;
}

void Enemy::Update(GlobalData& gData)
{
    ArrayManager<Player>& playerData = gData.Players;
    Player* const nearest_player = nearestPlayer(playerData);

    if (nearest_player)
    {
        Attack(*nearest_player);
    }
    else
    {
        // Retreat?
        Brake();
        printf("No target\n");
    }

    Ship::Update(gData);
}

Player* Enemy::nearestPlayer(ArrayManager<Player>& playerData) const
{
    Player* targetPlayer = nullptr;

    for (size_t i = 0; i < playerData.count(); i++)
    {
        Player& player = *playerData.get(i);

        if (player.isActive())
        {
            if (not player.isUnderCover())
            {
                const Vector2 position = player.getPosition();
                const Vector2 enemyPosition = getPosition();
                const Fix16 distance = position.DistanceToPoint(enemyPosition);

                if (!targetPlayer
                        ||
                    (distance < targetPlayer->getPosition().DistanceToPoint(enemyPosition)))
                {
                    targetPlayer = &player;
                }
            }
        }
    }

    return targetPlayer;
}

void Enemy::Attack(Player& player)
{
    Vector2 dist = player.getPosition() - getPosition();

    printf("X = %d, Y = %d\n", fix16_to_int(dist.X.value), fix16_to_int(dist.Y.value));

    Fix16 angle(fix16_atan2(dist.Y.value, dist.X.value));

    while (angle < 0)
    {
        angle += fix16_pi << 1;
    }

    if (abs(fix16_to_int(dist.DistanceSqrt().value)) < (96 * 96))
    {
        mDesiredAngle = angle;
        Brake();
    }
    else
    {
        angle *= FIX16_FROM_INT(180);
        angle /= fix16_pi;

        SetDesiredDirection(angle);
    }
}

void Enemy::SpawnBullet()
{
    return;
}
