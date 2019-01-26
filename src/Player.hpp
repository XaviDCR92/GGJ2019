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
    void Update(void* const data);
    void render(const Camera& camera);

private:
    Pad pad;
    const bool active;
    int calculateAngle(bool& change);
    void checkFire(void);
};

#endif /* PLAYER_H */
