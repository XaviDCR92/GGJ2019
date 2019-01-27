#pragma once

#include "Ship.hpp"

class GlobalData;
class Player;
template<class T>
class ArrayManager;

class Enemy : public Ship
{
public:
    Enemy();
    virtual void Update(GlobalData& gData) override;
    virtual void injured(void) override;

private:
    Player* nearestPlayer(ArrayManager<Player>& playerData);
    Planet* nearestPlanet(ArrayManager<Planet>& planets) const;
    Enemy* nearestEnemy(ArrayManager<Enemy>& enemies) const;
    void Attack(Player& player, GlobalData& gData);
    void SpawnBullet(ArrayManager<Blaster>& blasters);
    void MoveTo(const Vector2& position, const bool min);
    const Vector2 mInitPosition;
    uint32_t mFireCounter;
};

void EnemyInit(void);
