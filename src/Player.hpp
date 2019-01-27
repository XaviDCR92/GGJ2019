#ifndef PLAYER_H
#define PLAYER_H

/*******************************************************************//**
*
* \file     Player.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Player module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Pad.hpp"
#include "Ship.hpp"
#include "Gfx.h"
#include "Enemy.hpp"
#include "ArrayManager.hpp"
#include "GlobalData.h"
#include <stddef.h>
#include <stdbool.h>

class Player : public Ship
{
public:
    enum playern
    {
        PLAYER_ONE,
        PLAYER_TWO
    };

    Player(const playern _player_n, const bool _active, GsSprite& _spr);
    bool isActive(void) const;
    bool isUnderCover(void) const;
    void setUnderCover(const bool state);
    void setCollected(const bool state);
    void Update(GlobalData& gData);
    void render(const Camera& camera);
    bool isInvincible(void);
    virtual void injured(void) override;

private:
    Pad pad;
    bool active;
    bool mUnderCover;
    bool mCollected;
    int calculateAngle(bool& change);
    unsigned short mWaitTime, mInvincibleTime;
    bool mFlicker;
    void checkFire(ArrayManager<Blaster>& blasters);
};

#endif /* PLAYER_H */
