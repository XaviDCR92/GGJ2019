#include "Ship.hpp"
#include "Gfx.h"
#include "Sfx.h"
#include "Camera.hpp"
#include <stdio.h>
#include <stdlib.h>

static SsVag shipSnd, deathSnd;
static unsigned char voice;

void ShipInit(void)
{
    SfxUploadSound("DATA\\SOUNDS\\SHIP.VAG", &shipSnd);
    SfxUploadSound("DATA\\SOUNDS\\DEATH.VAG", &deathSnd);
}

Ship::Ship(GsSprite& spr) :
    SpaceEntity(spr),
    brake(true),
    mVoice(voice++),
    mVolume(MAX_VOLUME >> 3)
{
    SfxPlaySoundVolVoice(&shipSnd, mVoice, mVolume);
}

void Ship::Update(GlobalData&)
{
    UpdateLocation();
    UpdateRotation();
}

void Ship::death()
{
    SfxPlaySound(&deathSnd);
}

int Ship::GetRenderAngle() const
{
    /* Perform degrees to radians conversion. */
    Fix16 intermediate;

    intermediate.value = fix16_smul(mCurrentAngle.value, fix16_from_int(180));
    intermediate.value = fix16_div(intermediate.value, fix16_pi);

    return GfxFromDegrees(fix16_to_int(intermediate.value));
}

void Ship::GetRenderPosition(short& outX, short& outY) const
{
    outX = fix16_to_int(mPosition.X) - (mSpr.w >> 1);
    outY = fix16_to_int(mPosition.Y) - (mSpr.h >> 1);
}

void Ship::SetDesiredDirection(const int desiredAngle)
{
    SetDesiredDirection(Fix16(fix16_from_int(desiredAngle)));
}

void Ship::SetDesiredDirection(const Fix16 desiredAngle)
{
    /* Perform degrees to radians conversion. */
    Fix16 intermediate(desiredAngle * fix16_pi);
    mDesiredAngle.value = fix16_div(intermediate.value, fix16_from_int(180));

    mDesiredDirection.X.value = fix16_cos(mDesiredAngle);
    mDesiredDirection.Y.value = fix16_sin(mDesiredAngle);

    if (mSpeed < mMaxSpeed)
    {
        mSpeed += mAccel;
    }
    else
    {
        mSpeed = mMaxSpeed;
    }

    if ((mVolume + 64) < 0x1FFF)
    {
        mVolume += 64;
    }
    else
    {
        mVolume = 0x1FFF;
    }

    SfxVoiceVol(mVoice, mVolume);

    brake = false;
}

void Ship::Brake(void)
{
    brake = true;
}

void Ship::UpdateLocation()
{
    if (brake)
    {
        enum
        {
            DECCELERATION = 0xF00
        };

        if (mSpeed > DECCELERATION)
        {
            mSpeed -= DECCELERATION;
        }
        else
        {
            mSpeed = 0;
        }
    }

    if ((mVolume - 64) >= (MAX_VOLUME >> 3))
    {
        mVolume -= 64;
    }
    else
    {
        mVolume = (MAX_VOLUME >> 3);
    }

    const Fix16 newX = mPosition.X + (mCurrentDirection.X * mSpeed);
    const Fix16 newY = mPosition.Y + (mCurrentDirection.Y * mSpeed);

    if ((newX >= 0)
            &&
        (newY >= 0))
    {
        mPosition += mCurrentDirection * mSpeed;
    }
}

void Ship::UpdateRotation()
{
    const fix16_t same = mCurrentAngle.value + (fix16_pi << 1);
    const fix16_t same2 = mDesiredAngle.value + (fix16_pi << 1);

    const fix16_t dist1 = abs(same - mDesiredAngle.value);
    const fix16_t dist2 = abs(mCurrentAngle.value - mDesiredAngle.value);
    const fix16_t& angle = dist1 < dist2 ? same: mCurrentAngle.value;

    const fix16_t dist3 = abs(angle - same2);
    const fix16_t dist4 = abs(angle - mDesiredAngle.value);
    const fix16_t& dest_angle = dist3 < dist4 ? same2: mDesiredAngle.value;

    if (abs(angle - dest_angle) >= mTurnRate.value)
    {
        if (angle < dest_angle)
        {
            mCurrentAngle.value = angle + mTurnRate.value;
        }
        else if (angle > dest_angle)
        {
            mCurrentAngle.value = angle - mTurnRate.value;
        }
    }
    else
    {
        mCurrentAngle.value = mDesiredAngle.value;
    }

    mCurrentDirection.X.value = fix16_cos(mCurrentAngle);
    mCurrentDirection.Y.value = fix16_sin(mCurrentAngle);
}

void Ship::render(const Camera& camera)
{
    mSpr.rotate = GetRenderAngle();

    SpaceEntity::render(camera);
}
