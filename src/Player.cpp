/*******************************************************************//**
*
* \file     Player.c
*
* \author   Xavier Del Campo
*
* \brief    Implementation of Player module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Pad.hpp"
#include "Player.hpp"
#include "GlobalData.h"
#include "Blaster.hpp"
#include <limits.h>
#include <stdio.h>

/* *************************************
 * Defines
 * *************************************/

// Here I have used an old macro that I found on nextvolume's source code for "A Small Journey", IIRC.
// Totally fool-proof, so I dint' want to complicate things!
#define check_bb_collision(x1,y1,w1,h1,x2,y2,w2,h2) (!( ((x1)>=(x2)+(w2)) || ((x2)>=(x1)+(w1)) || \
                                                        ((y1)>=(y2)+(h2)) || ((y2)>=(y1)+(h1)) ))

/* *************************************
 * Types definition
 * *************************************/

/* *************************************
 * Global variables definition
 * *************************************/

/* *************************************
 * Local variables definition
 * *************************************/

/* *************************************
 *  Local prototypes declaration
 * *************************************/

/* *************************************
 * Functions definition
 * *************************************/

Player::Player(const playern _player_n, const bool _active, GsSprite& _spr) :
    Ship(_spr),
    pad(_player_n),
    active(_active),
    mUnderCover(false),
    mCollected(false),
    mWaitTime(0)
{
    mRotationSpeed = Fix16((uint16_t)3);
    mPosition = Vector2(40, 20);
    mMaxSpeed = FIX16_FROM_INT(3);
    mAccel = 0x1000;
    mTurnRate = 0x2200;
}

bool Player::isActive(void) const
{
    return active;
}

bool Player::isUnderCover(void) const
{
    return mUnderCover;
}

void Player::setCollected(const bool state)
{
    mCollected = state;
}

void Player::Update(GlobalData& gData)
{
    if (isActive())
    {
        pad.handler();

        Ship::Update(gData);

        bool any_pressed;

        const int angle = calculateAngle(any_pressed);

        if (any_pressed)
        {
            SetDesiredDirection(angle);
        }
        else
        {
            Brake();
        }

        enum
        {
            WAIT_TIME = 50 * 3
        };

        if (mWaitTime < USHRT_MAX)
        {
            mWaitTime++;
        }

        if (mWaitTime >= WAIT_TIME)
        {
            checkFire(gData.Blasters);
        }
    }
}

int Player::calculateAngle(bool& change)
{
    int angle = 0;
    change = true;

    if (pad.keyPressed(Pad::UP))
    {
        if (pad.keyPressed(Pad::LEFT))
        {
            angle = 235;
            mDesiredDirection = Vector2(-1, -1);
        }
        else if (pad.keyPressed(Pad::RIGHT))
        {
            angle = 315;

            mDesiredDirection = Vector2(1, -1);
        }
        else
        {
            mDesiredDirection = Vector2(0, -1);
            angle = 270;
        }
    }
    else if (pad.keyPressed(Pad::DOWN))
    {
        if (pad.keyPressed(Pad::LEFT))
        {
            angle = 135;
        }
        else if (pad.keyPressed(Pad::RIGHT))
        {
            angle = 45;
        }
        else
        {
            angle = 90;
        }
    }
    else if (pad.keyPressed(Pad::LEFT))
    {
        angle = 180;
    }
    else if (pad.keyPressed(Pad::RIGHT))
    {
        /* Default case. */
    }
    else
    {
        change = false;
    }

    return angle;
}

void Player::setUnderCover(const bool state)
{
    mUnderCover = state;
}

void Player::checkFire(ArrayManager<Blaster>& blasters)
{
    if (pad.singlePress(Pad::CROSS))
    {
        // Fire!
        blasters.AddElement(Blaster(mPosition, mCurrentAngle, Blaster::Shooter::PLAYER));

        mWaitTime = 0;
    }
}
