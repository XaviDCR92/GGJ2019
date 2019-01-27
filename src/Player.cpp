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
#include "Earth.hpp"
#include "Blaster.hpp"
#include <limits.h>
#include <stdio.h>

/* *************************************
 * Defines
 * *************************************/

enum
{
    INVINCIBILITY_TIME = 50 * 2,
    WAIT_TIME = 70
};

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

Player::Player(const playern _player_n, const bool _active, GsSprite& _spr, GsSprite& _sprRes) :
    Ship(_spr),
    pad(_player_n),
    mResources(_sprRes),
    active(_active),
    mUnderCover(false),
    mWaitTime(WAIT_TIME),
    mInvincibleTime(INVINCIBILITY_TIME),
    mFlicker(false)
{
    mRotationSpeed = Fix16((uint16_t)3);
    mPosition = Vector2(40, 20);
    mMaxSpeed = FIX16_FROM_INT(3);
    mAccel = 0x1000;
    mTurnRate = 0x2200;
    mHealth = 5;
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
    if(state)
        mResources.mStacks++;
    else if(mResources.mStacks > 0)
        mResources.mStacks--;

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

        if (mWaitTime < USHRT_MAX)
        {
            mWaitTime++;
        }

        if (mWaitTime >= WAIT_TIME)
        {
            checkFire(gData.Blasters);
        }
    }

    if(mResources.mStacks > 0 && isCollidingWith(gData.PlanetEarth))
    {
       gData.PlanetEarth.DumpResources(mResources.mStacks);
        mResources.mStacks = 0;
    }
}

bool Player::isInvincible(void)
{
    return mInvincibleTime;
}

void Player::injured(void)
{
    if (mHealth)
    {
        mHealth--;
    }

    if (mHealth)
    {
        printf("Lives remaining: %d\n", mHealth);
        mInvincibleTime = INVINCIBILITY_TIME;
    }
    else
    {
        printf("You have died!\n");
        setActive(false);
    }
}

bool Player::isFull()
{
    if(mResources.mStacks >= mResources.mMaxStacks)
        return true;
    return false;
}

void Player::render(const Camera& camera)
{
    if (isActive())
    {
        if (mInvincibleTime)
        {
            if (mFlicker ^= true)
            {
                Ship::render(camera);
            }

            mInvincibleTime--;
        }
        else
        {
            Ship::render(camera);
        }

        short x,y;
        GetRenderPosition(x,y);
        mResources.render(camera, x, y);
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
