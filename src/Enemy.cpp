#include "Enemy.hpp"
#include "Player.hpp"

void Enemy::Update()
{
    // TODO: Change the objective for the actual players position
    Vector2 objective(200, 200);
    mDesiredDirection = objective - mPosition;

    Attack();

    Ship::Update();
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

void SpawnBullet()
{
    return;
}