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
#include "Gfx.h"
#include "Sfx.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* *************************************
 * Defines
 * *************************************/

enum
{
    INVINCIBILITY_TIME = 50 * 2,
    WAIT_TIME = 30
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

static GsSprite heartSpr;
static SsVag chargeSnd;

/* *************************************
 *  Local prototypes declaration
 * *************************************/

/* *************************************
 * Functions definition
 * *************************************/

void PlayerInit(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\HEART.TIM", &heartSpr);
    SfxUploadSound("DATA\\SOUNDS\\CHARGE.VAG", &chargeSnd);
}

Player::Player(const playern _player_n, const bool _active, GsSprite& _spr, GsSprite& _sprRes) :
    Ship(_spr),
    mId(_player_n),
    mMaxHealth(5),
    pad(_player_n),
    mResources(_sprRes),
    active(_active),
    mUnderCover(false),
    mWaitTime(WAIT_TIME),
    mInvincibleTime(INVINCIBILITY_TIME),
    mUnderCoverTime(0),
    mFlicker(false),
    mWasUnderCover(false)
{
    mRotationSpeed = Fix16((uint16_t)3);
    mPosition = Vector2(rand() % (100 + 1) + 100, rand() % (100 + 1) + 100);
    mMaxSpeed = FIX16_FROM_INT(3);
    mAccel = 0x1000;
    mTurnRate = 0x2200;
    mHealth = mMaxHealth;
    mActive = _active;
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

    if (isUnderCover())
    {
        enum
        {
            HEALTH_RESTORE_TIME = 60
        };

        if (mUnderCoverTime < USHRT_MAX)
        {
            mUnderCoverTime++;
        }

        if (mUnderCoverTime > HEALTH_RESTORE_TIME)
        {
            if (mHealth < mMaxHealth)
            {
                mHealth++;
            }

            mUnderCoverTime = 0;
        }

        ArrayManager<Player>& players = gData.Players;
        bool connect = true;

        for (size_t i = 0; i < players.count(); i++)
        {
            if (players.get(i)->mWasUnderCover)
            {
                connect = false;
                break;
            }
        }

        if (connect)
        {
            SfxPlaySound(&chargeSnd);
        }
    }
    else
    {
        mUnderCoverTime = 0;

        ArrayManager<Player>& players = gData.Players;
        bool disconnect = true;

        for (size_t i = 0; i < players.count(); i++)
        {
            if (players.get(i)->isUnderCover())
            {
                disconnect = false;
                break;
            }
        }

        if (disconnect)
        {
            SfxStopSound(&chargeSnd);
        }
    }

    mWasUnderCover = isUnderCover();
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
        mInvincibleTime = INVINCIBILITY_TIME;
    }
    else
    {
        Ship::death();
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

    heartSpr.y = 16;

    switch (mId)
    {
        case playern::PLAYER_ONE:
        {
            for (unsigned int h = 0; h < mHealth; h++)
            {
                heartSpr.x = 16 + ((heartSpr.w + 2) * h);
                GfxSortSprite(&heartSpr);
            }
        }
        break;

        case playern::PLAYER_TWO:
        {
            for (unsigned int h = 0; h < mHealth; h++)
            {
                heartSpr.x = 256 + ((heartSpr.w + 2) * h);
                GfxSortSprite(&heartSpr);
            }
        }

        break;

        default:
        break;
    }

    short x,y;
    GetRenderPosition(x,y);
    mResources.render(camera, x, y);
}

int Player::calculateAngle(bool& change)
{
    int angle = 0;
    change = true;

    if (pad.keyPressed(Pad::UP))
    {
        if (pad.keyPressed(Pad::LEFT))
        {
            angle = 225;
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
        Vector2 pos(mPosition.X + (mRadius * mCurrentAngle.cos()),
                    mPosition.Y + (mRadius * mCurrentAngle.sin()));
        blasters.AddElement(Blaster(pos, mCurrentAngle, Blaster::Shooter::PLAYER));

        mWaitTime = 0;
    }
}
