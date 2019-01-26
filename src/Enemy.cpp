#include "Enemy.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include "GlobalData.h"
#include <stdio.h>

Enemy::Enemy(GsSprite& spr) :
    Ship(spr)
{
    mPosition = Vector2(120, 60);
}

void Enemy::Update(GlobalData& gData)
{
    Ship::Update(gData);

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
    }
}

Player* Enemy::nearestPlayer(ArrayManager<Player>& playerData) const
{
    Player* targetPlayer = nullptr;

    for (size_t i = 0; i < playerData.count(); i++)
    {
        Player& player = *playerData.get(i);

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

    printf("targetplayer = 0x%08X\n", targetPlayer);

    return targetPlayer;
}

void Enemy::Attack(Player& player)
{
    Vector2 dist = player.getPosition() - getPosition();

    SetDesiredDirection(Fix16(fix16_atan2(dist.X, dist.Y)));
}

void Enemy::SpawnBullet()
{
    return;
}
