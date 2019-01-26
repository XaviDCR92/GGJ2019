#include "Enemy.hpp"
#include "Player.hpp"
#include "ArrayManager.hpp"
#include <stdio.h>

Enemy::Enemy(GsSprite& spr, const Camera& camera) :
    Ship(spr, camera)
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
}

void Enemy::SpawnBullet()
{
    return;
}
