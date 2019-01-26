#include "Ship.hpp"
#include <stdio.h>

Ship::Ship() :
    mCurrentDirection(Vector2(1, 0))
{
}

void Ship::Update()
{
    UpdateLocation();
    UpdateRotation();
}

int Ship::GetRenderAngle()
{
    return mAngle >> 4;
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

    Fix16 intermediate(desiredAngle/360);
    mAngle = fix16_pi*intermediate.value;
    mAngle = mAngle % (fix16_pi*2);
    mDesiredDirection.X = fix16_sin(mAngle);
    mDesiredDirection.Y = fix16_cos(mAngle);
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
    Fix16 current_angle(fix16_atan2(mCurrentDirection.Y, mCurrentDirection.X));
    Fix16 desired_angle(fix16_atan2(mDesiredDirection.Y, mDesiredDirection.X));

    printf("c = %i\n", current_angle.value);

    Fix16 comp = desired_angle - current_angle;
    if(comp > fix16_pi || (comp < 0 && comp > -fix16_pi))
    {
       current_angle -= mRotationSpeed;
    }
    else
    {
        current_angle += mRotationSpeed;
    }

    SetDesiredDirection(current_angle);

}
