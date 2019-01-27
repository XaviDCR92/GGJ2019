#pragma once

#include "SpaceEntity.hpp"

class Camera;

class Blaster : public SpaceEntity
{
public:

    Blaster();
    virtual void Update(GlobalData& data) override;
    Blaster& operator=(const Blaster& other);

private:
};

void BlasterInit(void);
