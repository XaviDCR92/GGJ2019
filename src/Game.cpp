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

#include "GlobalData.h"
#include "Game.hpp"
#include "Gfx.h"
#include "Menu.h"
#include "Enemy.hpp"
#include "CollectableSource.hpp"
#include "Blaster.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "Timers.h"
#include "ArrayManager.hpp"
#include "Camera.hpp"
#include "Earth.hpp"
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

static GsSprite playerSpr, player2Spr, resourceBar;

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
        /* Load needed files. */
        GameInitFiles();

        /* Set first game initialization flag. */
        initDone = true;
    }
}

static void GameInitFiles(void)
{
    EnemyInit();
    PlanetInit();
    EarthInit();
    ResourcesInit();
    BlasterInit();
    GfxSpriteFromFile("DATA\\SPRITES\\PLAYER.TIM", &playerSpr);
    GfxSpriteFromFile("DATA\\SPRITES\\PLAYER2.TIM", &player2Spr);
    GfxSpriteFromFile("DATA\\SPRITES\\RES_BAR.TIM", &resourceBar);
}

static void GameLoop(const size_t players)
{
    Camera cam;
    Earth earth;

    // Players
    Player player_array[2] =
    {
        {Player::PLAYER_ONE, players > Player::PLAYER_ONE, playerSpr, resourceBar},
        {Player::PLAYER_TWO, players > Player::PLAYER_TWO, player2Spr, resourceBar}
    };

    ArrayManager<Player> pl(ARRAY_SIZE(player_array), player_array);

    // Enemies
    Enemy enemy_array[2];
    ArrayManager<Enemy> e(ARRAY_SIZE(enemy_array), enemy_array);

    // Planets
    Planet planet_array[1];
    ArrayManager<Planet> planets(ARRAY_SIZE(planet_array), planet_array);

    // Resources
    CollectableSource resources_array[1];
    ArrayManager<CollectableSource> resources(ARRAY_SIZE(resources_array), resources_array);

    // Blasters (lasers)
    Blaster blaster_array[20];
    ArrayManager<Blaster> blasters(ARRAY_SIZE(blaster_array), blaster_array);

    GlobalData data =
    {
        // ArrayManager<Player>& Players;
        pl,
        // ArrayManager<Enemy>& Enemies;
        e,
        // ArrayManager<Planet>& Planets;
        planets,
        // ArrayManager<CollectableSource>& Resources
        resources,
        //ArrayManager<Blaster>& Blasters
        blasters,
        // Earth&
        earth,
        // Camera& cam;
        cam
    };

    e.setActive(true);

    for (;;)
    {
        // Game logic
        pl.Update(data);
        e.Update(data);
        planets.Update(data);
        resources.Update(data);

        switch (players)
        {
            case 1:
                cam.Update(pl.get(Player::PLAYER_ONE)->getPosition());
            break;

            case 2:
                cam.Update( pl.get(Player::PLAYER_ONE)->getPosition(),
                            pl.get(Player::PLAYER_TWO)->getPosition());
            break;
        }

        blasters.Update(data);

        // Rendering
        while (GfxIsBusy());
        GfxClear();
        planets.render(cam);
        earth.render(cam);
        resources.render(cam);
        pl.render(cam);
        e.render(cam);
        blasters.render(cam);

        GfxDrawScene();
    }
}
