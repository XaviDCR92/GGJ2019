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
    void setInitPos(const Vector2& vec);

private:
    Player* nearestPlayer(ArrayManager<Player>& playerData);
    Planet* nearestPlanet(ArrayManager<Planet>& planets, Earth& earth) const;
    Enemy* nearestEnemy(ArrayManager<Enemy>& enemies) const;
    void Attack(Player& player, GlobalData& gData);
    void SpawnBullet(ArrayManager<Blaster>& blasters);
    void MoveTo(const Vector2& position, const bool min);
    uint32_t mFireCounter;
    Vector2 mInitPosition;
};

void EnemyInit(void);
