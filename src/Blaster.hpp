#pragma once

#include "SpaceEntity.hpp"
#include "Vector2.hpp"

class Camera;
class Player;
class Enemy;
template<class T>
class ArrayManager;

class Blaster : public SpaceEntity
{
public:
    enum Shooter
    {
        UNDEFINED,
        ENEMY,
        PLAYER
    };

    Blaster();
    Blaster(const Vector2& pos, const Fix16 angle, const Shooter shooter);
    virtual void Update(GlobalData& data) override;
    virtual void render(const Camera& camera);
    int GetRenderAngle() const;
    Blaster& operator=(const Blaster& other);

private:
    const Fix16 mAngle;
    const Shooter mShooter;
    Vector2 mCurrentDirection;
    void UpdateLocation(void);
    void PlayerCollision(ArrayManager<Player>& players);
    void EnemyCollision(ArrayManager<Enemy>& enemies);
    void PlanetCollision(ArrayManager<Planet>& planets);
};

void BlasterInit(void);
