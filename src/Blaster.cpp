#include "Blaster.hpp"
#include "Gfx.h"
#include "SpaceEntity.hpp"
#include "GlobalData.h"
#include "ArrayManager.hpp"
#include "Planet.hpp"
#include "Player.hpp"
#include <stdio.h>

static GsSprite blasterSprite;

void BlasterInit(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\PLAYER.TIM", &blasterSprite);
}

Blaster::Blaster() : SpaceEntity(blasterSprite),
    mAngle(0),
    mShooter(Blaster::Shooter::UNDEFINED),
    mCurrentDirection(Vector2())
{
}

Blaster::Blaster(const Vector2& pos, const Fix16 angle, const Blaster::Shooter shooter) : SpaceEntity(blasterSprite),
    mAngle(angle),
    mShooter(shooter),
    mCurrentDirection(Vector2(Fix16(fix16_cos(mAngle)), Fix16(fix16_sin(mAngle))))
{
    mPosition = pos;
}

void Blaster::render(const Camera& camera)
{
    mSpr.rotate = GetRenderAngle();

    SpaceEntity::render(camera);

    if (!GfxIsSpriteInsideScreenArea(&mSpr))
    {
        setActive(false);
    }
}

void Blaster::Update(GlobalData& data)
{
    UpdateLocation();

    switch (mShooter)
    {
        case Shooter::ENEMY:
            PlayerCollision(data.Players);
            PlanetCollision(data.Planets);
        break;

        case Shooter::PLAYER:
            EnemyCollision(data.Enemies);
        break;

        case Shooter::UNDEFINED:
            // Fall through.
        default:
        break;
    }
}

void Blaster::PlayerCollision(ArrayManager<Player>& players)
{
    if (isActive())
    {
        for (size_t i = 0; i < players.count(); i++)
        {
            Player& player = *players.get(i);

            if (isCollidingWith(player))
            {
                printf("You got injured!\n");
                setActive(false);

                break;
            }
        }
    }
}

void Blaster::PlanetCollision(ArrayManager<Planet>& planets)
{
    if (isActive())
    {
        for (size_t i = 0; i < planets.count(); i++)
        {
            Planet& planet = *planets.get(i);

            if (isCollidingWith(planet))
            {
                setActive(false);
                break;
            }
        }
    }
}

void Blaster::EnemyCollision(ArrayManager<Enemy>& enemies)
{
    if (isActive())
    {
        for (size_t i = 0; i < enemies.count(); i++)
        {
            Enemy& enemy = *enemies.get(i);

            if (isCollidingWith(enemy))
            {
                printf("Enemy got injured!\n");
                setActive(false);
                break;
            }
        }
    }
}

void Blaster::UpdateLocation(void)
{
    if (isActive())
    {
        enum
        {
            SPEED = 0x47FFB
        };

        mPosition += mCurrentDirection * SPEED;
    }
}

int Blaster::GetRenderAngle() const
{
    /* Perform degrees to radians conversion. */
    Fix16 intermediate;

    intermediate.value = fix16_smul(mAngle.value, fix16_from_int(180));
    intermediate.value = fix16_div(intermediate.value, fix16_pi);

    return GfxFromDegrees(fix16_to_int(intermediate.value));
}

Blaster& Blaster::operator=(const Blaster& other)
{
    const_cast<Fix16&>(mAngle) = other.mAngle;
    mCurrentDirection = other.mCurrentDirection;
    mActive = other.mActive;
    mSpr = other.mSpr;
    mArrayIdx = other.mArrayIdx;
    mRadius = other.mRadius;
    mPosition = other.mPosition;
    const_cast<Shooter&>(mShooter) = other.mShooter;

    return *this;
}
