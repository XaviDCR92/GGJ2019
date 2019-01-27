#include "Enemy.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "ArrayManager.hpp"
#include "GlobalData.h"
#include <stdio.h>
#include <stdlib.h>

Enemy::Enemy(GsSprite& spr) :
    Ship(spr),
    mInitPosition(Vector2(10, 200))
{
    mPosition = mInitPosition;
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
        if (!nearestPlanet(gData.Planets))
        {
            Attack(*nearest_player);
        }
        else
        {
            // Retreat
            printf("Retreat\n");
            MoveTo(mInitPosition, false);
        }
    }
    else
    {
        // Retreat
        MoveTo(mInitPosition, false);
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

Planet* Enemy::nearestPlanet(ArrayManager<Planet>& planets) const
{
    Planet* targetPlanet = nullptr;

    for (size_t i = 0; i < planets.count(); i++)
    {
        Planet& planet = *planets.get(i);

        if (planet.isActive())
        {
            const Vector2 position = planet.getPosition();
            const Vector2 enemyPosition = getPosition();
            const Fix16 distance = position.DistanceToPoint(enemyPosition);

            if (distance >= 0)
            {
                if (distance < (mRadius << 1))
                {
                    targetPlanet = &planet;
                }
            }
        }
    }

    return targetPlanet;
}

void Enemy::Attack(Player& player)
{
    MoveTo(player.getPosition(), true);
}

void Enemy::MoveTo(const Vector2& position, const bool min)
{
    Vector2 dist = position - getPosition();

    Fix16 angle(fix16_atan2(dist.Y.value, dist.X.value));

    while (angle < 0)
    {
        angle += fix16_pi << 1;
    }

    if (min && abs(fix16_to_int(dist.DistanceSqrt().value)) < (96 * 96))
    {
        // Stare at the player without moving.
        mDesiredAngle = angle;
        Brake();
    }
    else
    {
        angle *= FIX16_FROM_INT(180);
        angle /= fix16_pi;

        printf("Moving..\n");
        SetDesiredDirection(angle);
    }
}

void Enemy::SpawnBullet()
{
    return;
}
