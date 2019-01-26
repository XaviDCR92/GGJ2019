#pragma once

#include "Vector2.hpp"

class Ship
{
public:

    Ship();
    void UpdateTransform();

    int GetRenderAngle();
    void GetRenderPosition(int& X, int& Y);    

protected:

    // Both take DEGREES
    void SetDesiredDirection(int desiredAngle = 0);
    void SetDesiredDirection(Fix16 desiredAngle);
    int GetAngleToDesired();

    Vector2 mPosition;
    Fix16 mAngle;
    Fix16 mSpeed, mRotationSpeed;
    Vector2 mDesiredDirection, mCurrentDirection;

private:

    void UpdateLocation();
    void UpdateRotation();

};