#ifndef GFX_H
#define GFX_H

/*******************************************************************//**
*
* \file     Gfx.h
*
* \author   Xavier Del Campo
*
* \brief    Include file for Gfx module.
*
************************************************************************/

/*******************************************************************//**
*
* \defgroup GFX   Gfx
*
*           This module provides high-level interaction with primitives
*           and PSX graphics sinthetizer (GPU).
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include <psxgpu.h>
#include <stdbool.h>

/* *************************************
 * Defines
 * *************************************/

#define SPRITE_INDEX_INVALID    (size_t)(0xFFFFFFFF)

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

/* *************************************
 * Public types definition
 * *************************************/

enum
{
    X_SCREEN_RESOLUTION = 384,
    Y_SCREEN_RESOLUTION = 240
};

/* *************************************
 * Public variables declaration
 * *************************************/

/* *************************************
 * Public functions declaration
 * *************************************/

EXTERNC void GfxInit(void);
EXTERNC bool GfxSpriteFromFile(const char* const strFilePath, GsSprite* const pSpr);
EXTERNC void GfxSortSprite(GsSprite* const psSpr);
EXTERNC bool GfxIsInsideScreenArea(const short x, const short y, const short w, const short h);
EXTERNC void GfxDrawScene(void);

/** \} */

#endif /* GFX_H */
