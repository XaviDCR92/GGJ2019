#include "Enemy.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include <stdio.h>

Enemy::Enemy(GsSprite& spr) :
    Ship(spr)
{
    mPosition = Vector2(60, 60);
}

void Enemy::Update(void* const data)
{
    Ship::Update(data);

    Vector2 minDistance(0x7FFF, 0x7FFF);
    ArrayManager<Player>& playerData = *static_cast<ArrayManager<Player> *>(data);

    Player* const nearest_player = nearestPlayer(playerData);

    if (nearest_player)
    {
        Attack(*nearest_player);
    }
    else
    {
        // Retreat?
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
