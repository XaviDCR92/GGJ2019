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
    pad(_player_n),
    active(_active),
    spr(_spr)
{
    mRotationSpeed = Fix16((uint16_t)3);
    mSpeed = Fix16((int16_t)3);

    mPosition.X = Fix16((int16_t)40);
    mPosition.Y = Fix16((int16_t)20);
}

bool Player::isActive(void)
{
    return active;
}

void Player::handler(void)
{
    if (isActive())
    {
        pad.handler();

        Ship::UpdateTransform();

        SetDesiredDirection(calculateAngle());

        checkFire();

        render();
    }
}

int Player::calculateAngle(void)
{
    int angle = 0;

    if (pad.keyPressed(Pad::UP))
    {
        if (pad.keyPressed(Pad::LEFT))
        {
            angle = 235;
        }
        else if (pad.keyPressed(Pad::RIGHT))
        {
            angle = 315;
        }
        else
        {
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

    return angle;
}

void Player::checkFire(void)
{
}

void Player::render(void)
{
    int x, y;

    Ship::GetRenderPosition(x, y);

    spr.x = x;
    spr.y = y;
    spr.rotate = GetRenderAngle();
    spr.mx = spr.w >> 1;
    spr.my = spr.h >> 1;

    GfxSortSprite(&spr);
}
