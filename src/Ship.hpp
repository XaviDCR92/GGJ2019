#pragma once

#include "SpaceEntity.hpp"

class Camera;

class Ship : public SpaceEntity
{
public:

    Ship(GsSprite& spr);
    virtual void Update(GlobalData&);

    int GetRenderAngle() const;
    void GetRenderPosition(short& X, short& Y) const;
    void render(const Camera& camera);

protected:

    // Both take DEGREES
    void SetDesiredDirection(const int desiredAngle);
    void SetDesiredDirection(const Fix16 desiredAngle);
    void Brake(void);
    void death(void);

    Fix16 mDesiredAngle, mCurrentAngle;
    Fix16 mSpeed, mRotationSpeed;
    Vector2 mDesiredDirection, mCurrentDirection;
    Fix16 mMaxSpeed, mAccel, mTurnRate;

private:
    bool brake;
    const unsigned char mVoice;
    unsigned short mVolume;
    void UpdateLocation();
    void UpdateRotation();
};

void ShipInit(void);
