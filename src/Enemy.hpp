#pragma once

#include "Ship.hpp"

class Camera;

class Enemy : public Ship
{
public:
    Enemy(GsSprite& spr, const Camera& camera);
    virtual void Update(void* const data) override;

private:
    void Attack();
    void SpawnBullet();
};
