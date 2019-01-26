#pragma once

#include "Ship.hpp"

class GlobalData;
class Player;
template<class T>
class ArrayManager;

class Enemy : public Ship
{
public:
    Enemy(GsSprite& spr);
    virtual void Update(GlobalData& gData) override;

private:
    Player* nearestPlayer(ArrayManager<Player>& playerData) const;
    void Attack(Player& player);
    void SpawnBullet();
};
