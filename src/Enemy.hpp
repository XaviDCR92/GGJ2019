#pragma once

#include "Ship.hpp"

class Player;
template<class T>
class ArrayManager;

class Enemy : public Ship
{
public:
    Enemy(GsSprite& spr);
    virtual void Update(void* const data) override;

private:
    Player* nearestPlayer(ArrayManager<Player>& playerData) const;
    void Attack(Player& player);
    void SpawnBullet();
};
