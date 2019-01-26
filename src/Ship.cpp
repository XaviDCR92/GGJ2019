#include "Ship.hpp"
#include <stdio.h>

Ship::Ship()
{
}

void Ship::Update()
{
    //~ UpdateLocation();
    //~ UpdateRotation();
}

int Ship::GetRenderAngle()
{
    /* Perform degrees to radians conversion. */
    Fix16 intermediate;

    intermediate.value = fix16_smul(mAngle.value, fix16_from_int(180));

    intermediate.value = fix16_div(intermediate.value, fix16_pi);

    //~ printf("mAngle = %d\n", mAngle.value);
    return fix16_to_int(intermediate.value) * 4096;
}

void Ship::GetRenderPosition(int& outX, int& outY)
{
    outX = fix16_to_int(mPosition.X);
    outY = fix16_to_int(mPosition.Y);
}

void Ship::SetDesiredDirection(int desiredAngle)
{
    SetDesiredDirection(Fix16(fix16_from_int(desiredAngle)));
}

void Ship::SetDesiredDirection(Fix16 desiredAngle)
{
    /* Perform degrees to radians conversion. */
    Fix16 intermediate(desiredAngle * fix16_pi);
    mAngle.value = fix16_div(intermediate.value, fix16_from_int(180));

    mDesiredDirection.X.value = fix16_cos(mAngle);
    mDesiredDirection.Y.value = fix16_sin(mAngle);
}

int Ship::GetAngleToDesired()
{
    Fix16 current_angle(fix16_atan2(mCurrentDirection.Y, mCurrentDirection.X));
    Fix16 desired_angle(fix16_atan2(mDesiredDirection.Y, mDesiredDirection.X));

    Fix16 angle = desired_angle - current_angle;
    if (angle > fix16_pi)
        angle -= (fix16_pi*2);
    else if (angle < -fix16_pi)
        angle += (fix16_pi*2);

    return fix16_to_int(angle);
}

void Ship::UpdateLocation()
{
    mPosition += mCurrentDirection*mSpeed;
}

void Ship::UpdateRotation()
{
}
