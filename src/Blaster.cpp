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
    GfxSpriteFromFile("DATA\\SPRITES\\BLASTER.TIM", &blasterSprite);
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

    switch (mShooter)
    {
        case PLAYER:
            mSpr.r = 0;
            mSpr.g = NORMAL_LUMINANCE;
            mSpr.b = 0;
            break;

        case ENEMY:
            mSpr.r = NORMAL_LUMINANCE;
            mSpr.g = 0;
            mSpr.b = 0;
            break;

        case UNDEFINED:
            // Fall through.
        default:
        break;
    }

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
            data.Players.collision(*this);
        break;

        case Shooter::PLAYER:
            data.Enemies.collision(*this);
        break;

        case Shooter::UNDEFINED:
            // Fall through.
        default:
        break;
    }
}

void Blaster::UpdateLocation(void)
{
    if (isActive())
    {
        enum
        {
            SPEED = 0x50FB0
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
