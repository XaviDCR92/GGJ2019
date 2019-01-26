#pragma once 

#include "Ship.hpp"

class Enemy : public Ship
{
public:

    virtual void Update() override;

private:
    void Attack();
    void SpawnBullet();
};