/***************************************************************************//**
*
* \file     Game.cpp
*
* \brief    Game main module and entry point for game logic.
*
*******************************************************************************/

/* *****************************************************************************
 * Includes
 * ****************************************************************************/

#include "Game.hpp"
#include "Gfx.h"
#include "Menu.h"
#include "Player.hpp"
#include "Timers.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* *****************************************************************************
 * Defines
 * ****************************************************************************/

/* *****************************************************************************
 * Types definition
 * ****************************************************************************/

/* *****************************************************************************
 * Global variables definition
 * ****************************************************************************/

/* *****************************************************************************
 * Local variables definition
 * ****************************************************************************/

static GsSprite enemyShip;

/* *****************************************************************************
 * Local prototypes declaration
 * ****************************************************************************/

static void GameStart(const size_t players);
static void GameInit(const size_t players);
static void GameInitFiles(void);
static void GameLoop(Player &p1, Player &p2);

/* *****************************************************************************
 * Functions definition
 * ****************************************************************************/

/***************************************************************************//**
*
* \brief    Game logic entry point.
*
*******************************************************************************/
void Game(void)
{
    /* Execute game main menu and determine
     * next steps depending on its result. */
    switch (Menu())
    {
        case MENU_RESULT_GAME_START:
            /* Start gameplay given number of players. */
            GameStart(2);
        break;

        case MENU_RESULT_UNDEFINED:
            /* Fall through. */
        default:
            /* Invalid result. Restart game. */
        break;
    }
}

/***************************************************************************//**
*
* \brief    Initializes a level indicated by eSelectedLevel and
*           all game structures.
*
* \param    players
*               Number of active players.
*
*******************************************************************************/
static void GameStart(const size_t players)
{
    Player p1(Player::PLAYER_ONE);
    Player p2(Player::PLAYER_TWO);

    /* Game initialization. */
    GameInit(players);

    /* Gameplay. */
    GameLoop(p1, p2);
}

/***************************************************************************//**
*
* \brief    Initializes basic elements.
*
* \param    players
*               Number of active players.
*
*******************************************************************************/
static void GameInit(const size_t players)
{
    static bool initDone;

    if (!initDone)
    {
        /* Calculate random seed based on timer counter values. */
        const int seed = RootCounter1Get() ^ RootCounter2Get();

        /* Set random seed based on timer counters. */
        srand(seed);

        /* Load needed files. */
        GameInitFiles();

        /* Set first game initialization flag. */
        initDone = true;
    }
}

static void GameInitFiles(void)
{
    GfxSpriteFromFile("DATA\\SPRITES\\ENEMY.TIM", &enemyShip);
}

static void GameLoop(Player &p1, Player &p2)
{
    for (;;);
}
