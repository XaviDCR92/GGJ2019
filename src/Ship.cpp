#include "Ship.hpp"
#include "Gfx.h"
#include "Camera.hpp"
#include <stdio.h>
#include <stdlib.h>

Ship::Ship(GsSprite& spr, const Camera& cam) :
    SpaceEntity(spr, cam),
    brake(true)
{
}

void Ship::Update(void* const)
{
    UpdateLocation();
    UpdateRotation();
}

int Ship::GetRenderAngle() const
{
    /* Perform degrees to radians conversion. */
    Fix16 intermediate;

    //printf("mCurrentAngle.value = %d\n", mCurrentAngle.value);

    intermediate.value = fix16_smul(mCurrentAngle.value, fix16_from_int(180));
    intermediate.value = fix16_div(intermediate.value, fix16_pi);

    return GfxFromDegrees(fix16_to_int(intermediate.value));
}

void Ship::GetRenderPosition(int& outX, int& outY) const
{
    outX = fix16_to_int(mPosition.X);
    outY = fix16_to_int(mPosition.Y);
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

    enum
    {
        MAX_SPEED = FIX16_FROM_INT(3)
    };

    if (mSpeed < MAX_SPEED)
    {
        enum
        {
            ACCEL_RATE = 0x1000
        };

        mSpeed += ACCEL_RATE;
    }
    else
    {
        mSpeed = MAX_SPEED;
    }

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
            DECCELERATION = 0xA00
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

    mPosition += mCurrentDirection * mSpeed;
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

    if (abs(angle - dest_angle) >= 0x2200)
    {
        if (angle < dest_angle)
        {
            mCurrentAngle.value = angle + 0x2200;
        }
        else if (angle > dest_angle)
        {
            mCurrentAngle.value = angle - 0x2200;
        }
    }
    else
    {
        mCurrentAngle.value = mDesiredAngle.value;
    }

    mCurrentDirection.X.value = fix16_cos(mCurrentAngle);
    mCurrentDirection.Y.value = fix16_sin(mCurrentAngle);
}
