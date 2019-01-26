#pragma once

#include "SpaceEntity.hpp"

class Ship : public SpaceEntity
{
public:

    Ship();
    virtual void Update(void* const);

    int GetRenderAngle();
    void GetRenderPosition(int& X, int& Y);

protected:

    // Both take DEGREES
    void SetDesiredDirection(int desiredAngle);
    void SetDesiredDirection(Fix16 desiredAngle);
    int GetAngleToDesired();
    void Brake(void);

    Fix16 mAngle;
    Fix16 mSpeed, mRotationSpeed;
    Vector2 mDesiredDirection, mCurrentDirection;

private:
    bool brake;
    void UpdateLocation();
    void UpdateRotation();

};
