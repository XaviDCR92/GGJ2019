#pragma once

#include "SpaceEntity.hpp"

class Ship : public SpaceEntity
{
public:

    explicit Ship(GsSprite& spr);
    virtual void Update(void* const);

    int GetRenderAngle() const;
    void GetRenderPosition(int& X, int& Y) const;

protected:

    // Both take DEGREES
    void SetDesiredDirection(const int desiredAngle);
    void SetDesiredDirection(const Fix16 desiredAngle);
    void Brake(void);

    Fix16 mDesiredAngle, mCurrentAngle;
    Fix16 mSpeed, mRotationSpeed;
    Vector2 mDesiredDirection, mCurrentDirection;

private:
    bool brake;
    void UpdateLocation();
    void UpdateRotation();

};
