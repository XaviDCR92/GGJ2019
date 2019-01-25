#ifndef PAD_H
#define PAD_H

/*******************************************************************//**
*
* @file     Pad.h
*
* @author   Xavier Del Campo
*
* @brief    Include file for Pad module.
*
************************************************************************/

/* *************************************
 * Includes
 * *************************************/

#include <stdint.h>
#include <stdbool.h>
#include <psx.h>

/* *************************************
 * Defines
 * *************************************/

/* *************************************
 * Public types definition
 * *************************************/

class Pad
{
    public:
        enum Key
        {
            KEY_L2,
            KEY_R2,
            KEY_L1,
            KEY_R1,
            KEY_TRIANGLE,
            KEY_CIRCLE,
            KEY_CROSS,
            KEY_SQUARE,
            KEY_SELECT,
            KEY_LANALOGB,
            KEY_RANALOGB,
            KEY_START,
            KEY_UP,
            KEY_RIGHT,
            KEY_DOWN,
            KEY_LEFT,

            MAX_KEYS
        };

        Pad(const unsigned int _pad_n);
        void handler(void);
        bool keyPressed(const enum Key key);
        psx_pad_types getType(void);

    private:
        enum
        {
            RAW_DATA_SIZE = 16
        };

        uint8_t rawData[RAW_DATA_SIZE];
        psx_pad_state state;
        const unsigned int pad_n;
};

#endif /* PAD_H */
