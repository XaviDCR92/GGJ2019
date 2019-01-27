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
    Planet* nearestPlanet(ArrayManager<Planet>& planets) const;
    void Attack(Player& player);
    void SpawnBullet();
    void MoveTo(const Vector2& position, const bool min);
    const Vector2 mInitPosition;
};
