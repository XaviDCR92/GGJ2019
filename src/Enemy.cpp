#include "Enemy.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include <stdio.h>

Enemy::Enemy(GsSprite& spr) :
    Ship(spr)
{
    printf("Enemy constructor\n");
}

void Enemy::Update(void* const data)
{
    Ship::Update(data);

    ArrayManager<Player>& playerData = *static_cast<ArrayManager<Player> *>(data);

    // TODO: Change the objective for the actual players position
    Vector2 objective(200, 200);
    mDesiredDirection = objective - mPosition;

    Attack();

    Ship::Update(data);
}

void Enemy::Attack()
{
    const int shot_try_angle = 15;

    int angle = GetAngleToDesired();
    if(angle < 0)
        angle = -angle;
    if(angle < shot_try_angle)
        SpawnBullet();
}

void Enemy::SpawnBullet()
{
    return;
}
