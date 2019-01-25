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
#include <stddef.h>
#include <stdbool.h>

/* *************************************
 * Defines
 * *************************************/

/* *************************************
 * Public types definition
 * *************************************/

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

class Player
{
    public:
        enum playern
        {
            PLAYER_ONE,
            PLAYER_TWO
        };

        Player(const playern _player_n);
        bool isActive(void);
        void handler(void);

    private:
        Pad pad;
};

#endif /* PLAYER_H */
