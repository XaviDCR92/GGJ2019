#ifndef GAME_H
#define GAME_H

/*******************************************************************//**
*
* \file     Game.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Game module.
*
************************************************************************/


/* *************************************
 * Includes
 * *************************************/

/* *************************************
 * Defines
 * *************************************/

/* *************************************
 * Public types definition
 * *************************************/

enum tLevel
{
    LEVEL_1,

    MAX_LEVELS,
    LEVEL_UNDEFINED = MAX_LEVELS
};

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

#ifdef __cplusplus

extern "C" void Game(void);
#else
void Game(void);
#endif

#endif /* GAME_H */
