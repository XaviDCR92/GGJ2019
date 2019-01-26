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
#include "Enemy.hpp"
#include "Player.hpp"
#include "Timers.h"
#include "ArrayManager.hpp"
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
static void GameLoop(const size_t players);

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
    /* Game initialization. */
    GameInit(players);

    /* Gameplay. */
    GameLoop(players);
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

#define ARRAY_SIZE(a)   (sizeof (a) / sizeof (a[0]))

static void GameLoop(const size_t players)
{
    Player player_array[2] =
    {
        {Player::PLAYER_ONE, players >= Player::PLAYER_ONE, enemyShip},
        {Player::PLAYER_TWO, players >= Player::PLAYER_TWO, enemyShip}
    };
    ArrayManager<Player> pl(ARRAY_SIZE(player_array), player_array);

    Enemy enemy_array[2] =
    {
        {enemyShip},
        {enemyShip}
    };
    ArrayManager<Enemy> e(ARRAY_SIZE(enemy_array), enemy_array);

    for (;;)
    {
        GfxClear();

        pl.Update(&e);

        GfxDrawScene();
    }
}
