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
#include "Timers.h"
#include <assert.h>
#include <psx.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/* *************************************
 * Defines
 * *************************************/

#define PAD_CHECK(p) STATIC_ASSERT((1 << p) == PAD_##p);

/* *************************************
 * Types definition
 * *************************************/

/* *************************************
 * Global variables definition
 * *************************************/

/* *************************************
 * Local variables definition
 * *************************************/

static uint64_t timer;

/* *************************************
 *  Local prototypes declaration
 * *************************************/

/* *************************************
 * Functions definition
 * *************************************/

Pad::Pad(const unsigned int _pad_n) :
    rawData{0},
    prev{0},
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
}

void Pad::handler(void)
{
        timer++;

    prev = state;
    pad_read_raw(pad_n, rawData);
    PSX_PollPad_Fast_Ex(rawData, &state);
}

psx_pad_types Pad::getType(void)
{
    return static_cast<psx_pad_types>(state.type);
}

bool Pad::keyPressed(const enum Pad::Key key)
{
    static bool entered;

    if (not entered)
    {
        /* Calculate random seed based on timer counter values. */
        const int rootcounters = RootCounter1Get() ^ RootCounter2Get();

        /* Set random seed based on timer counters. */
        srand(rootcounters ^ ~timer);

        entered = true;
    }

    return state.buttons & (1 << key);
}

bool Pad::singlePress(const enum Pad::Key key)
{
    return keyPressed(key) && !(prev.buttons & (1 << key));
}

bool Pad::released(const enum Pad::Key key)
{
    return !keyPressed(key) && (prev.buttons & (1 << key));
}
