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

    mPosition = Vector2(40, 20);
}

bool Player::isActive(void)
{
    return active;
}

void Player::Update(void* const data)
{
    ArrayManager<Enemy>& e = *(ArrayManager<Enemy>*)data;

    if (isActive())
    {
        pad.handler();

        Ship::Update(data);

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

        checkFire();

        render();
    }
}

void Player::print(void)
{
    printf("I am a Player!\n");
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
