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
    mInitPosition(Vector2(rand() % (300 - 10 + 1) + 10, rand() % (300 - 10 + 1) + 10)),
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
        if (!nearestPlanet(gData.Planets)
                    &&
            !nearestEnemy(gData.Enemies))
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

Enemy* Enemy::nearestEnemy(ArrayManager<Enemy>& enemies) const
{
    Enemy* targetEnemy = nullptr;

    for (size_t i = 0; i < enemies.count(); i++)
    {
        if (enemies.get(i) != this)
        {
            Enemy& enemy = *enemies.get(i);

            if (enemy.isActive())
            {
                const Vector2 position = enemy.getPosition();
                const Vector2 enemyPosition = getPosition();
                const Fix16 distance = position.DistanceToPoint(enemyPosition);

                if (distance >= 0)
                {
                    if (distance < (mRadius << 1))
                    {
                        targetEnemy = &enemy;
                    }
                }
            }
        }
    }

    return targetEnemy;
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
        MIN_TIMER = 200,
        MAX_TIMER = 400
    };

    const unsigned int random = rand() % (MAX_TIMER - MIN_TIMER + 1) + MIN_TIMER;

    if (mFireCounter >= random)
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
    blasters.AddElement(Blaster(mPosition, mCurrentAngle, Blaster::Shooter::ENEMY));
}
