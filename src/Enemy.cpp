#include "Enemy.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "ArrayManager.hpp"
#include "GlobalData.h"
#include "Blaster.hpp"
#include "Gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static GsSprite enemyShip;

void EnemyInit(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\ENEMY.TIM", &enemyShip);
}

Enemy::Enemy() :
    Ship(enemyShip),
    mInitPosition(Vector2(10, 200)),
    mFireCounter(0)
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

    if (mFireCounter < ULONG_MAX)
    {
        mFireCounter++;
    }

    if (nearest_player)
    {
        if (!nearestPlanet(gData.Planets))
        {
            Attack(*nearest_player, gData);
        }
        else
        {
            // Retreat
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

                if (distance >= 0)
                {
                    if (!targetPlayer
                            ||
                        (distance < targetPlayer->getPosition().DistanceToPoint(enemyPosition)))
                    {
                        targetPlayer = &player;
                    }
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

void Enemy::Attack(Player& player, GlobalData& gData)
{
    MoveTo(player.getPosition(), true);

    enum
    {
        MIN_TIMER = 300,
        MAX_TIMER = 1500
    };

    const unsigned int random = rand() % (MAX_TIMER - MIN_TIMER + 1) + MIN_TIMER;

    if (random < mFireCounter)
    {
        SpawnBullet(gData.Blasters);
        mFireCounter = 0;
    }
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

        SetDesiredDirection(angle);
    }
}

void Enemy::SpawnBullet(ArrayManager<Blaster>& blasters)
{
    Blaster b(mPosition, mCurrentAngle, Blaster::Shooter::ENEMY);

    printf("Fire!\n");

    blasters.AddElement(b);
}
