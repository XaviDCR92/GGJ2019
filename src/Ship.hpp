#pragma once

#include "SpaceEntity.hpp"

class Ship : public SpaceEntity
{
public:

    Ship();
    virtual void Update();

    int GetRenderAngle();
    void GetRenderPosition(int& X, int& Y);    

protected:

    // Both take DEGREES
    void SetDesiredDirection(int desiredAngle = 0);
    void SetDesiredDirection(Fix16 desiredAngle);
    int GetAngleToDesired();

    Fix16 mAngle;
    Fix16 mSpeed, mRotationSpeed;
    Vector2 mDesiredDirection, mCurrentDirection;

private:

    void UpdateLocation();
    void UpdateRotation();

};