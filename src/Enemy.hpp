#pragma once

#include "Ship.hpp"

class Enemy : public Ship
{
public:

    Enemy();
    virtual void Update(void* const data) override;

private:
    void Attack();
    void SpawnBullet();
};
