/*******************************************************************//**
*
* \file     Pad.c
*
* \author   Xavier Del Campo
*
* \brief    Implementation of Pad module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include "Player.hpp"
#include "Pad.hpp"
#include <assert.h>
#include <psx.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* *************************************
 * Defines
 * *************************************/

#define PAD_CHECK(p) STATIC_ASSERT((1 << KEY_##p) == PAD_##p);

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

Pad::Pad(const unsigned int _pad_n) :
    pad_n(_pad_n)
{
    /* Perform compile-time assertions
     * in order to ensure consistency
     * between high-level and low-level definitions. */
    PAD_CHECK(LEFT);
    PAD_CHECK(RIGHT);
    PAD_CHECK(UP);
    PAD_CHECK(DOWN);
    PAD_CHECK(L2);
    PAD_CHECK(R2);
    PAD_CHECK(L1);
    PAD_CHECK(R1);
    PAD_CHECK(TRIANGLE);
    PAD_CHECK(CIRCLE);
    PAD_CHECK(CROSS);
    PAD_CHECK(SQUARE);
    PAD_CHECK(SELECT);
    PAD_CHECK(LANALOGB);
    PAD_CHECK(RANALOGB);
    PAD_CHECK(START);

    memset(rawData, 0, Pad::RAW_DATA_SIZE);
}

void Pad::handler(void)
{
    pad_read_raw(pad_n, rawData);

    PSX_PollPad_Fast_Ex(rawData, &state);
}

psx_pad_types Pad::getType(void)
{
    return static_cast<psx_pad_types>(state.type);
}

/*******************************************************************//**
*
* \brief
*
************************************************************************/
bool Pad::keyPressed(const enum Pad::Key key)
{
    return state.buttons & (1 << key);
}
