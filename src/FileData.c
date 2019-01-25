/***************************************************************************//**
*
* \file     FileData.c
*
* \brief    Implementations file for FileData module.
*
*******************************************************************************/

/* *****************************************************************************
 * Includes
 * ****************************************************************************/

#include "FileData.h"
#include "Gfx.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

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

/* *****************************************************************************
 * Local prototypes declaration
 * ****************************************************************************/

/* *****************************************************************************
 * Functions definition
 * ****************************************************************************/

bool FileDataLoadList(struct FileData* const* const fileList, const size_t files)
{
    if (fileList != NULL)
    {
        size_t i;

        for (i = 0; i < files; i++)
        {
            if (!FileDataLoad(fileList[i]))
            {
                return false;
            }
        }
    }

    return true;
}

/***************************************************************************//**
*
* \brief    Game logic entry point.
*
*******************************************************************************/
bool FileDataLoad(struct FileData* const fileData)
{
    if (fileData != NULL)
    {
        switch (fileData->dataType)
        {
            case DATA_TYPE_SPRITE:
                return GfxSpriteFromFile(fileData->path, fileData->data);
            break;

            case DATA_TYPE_SOUND:
            break;

            case DATA_TYPE_UNDEFINED:
                /* Fall through. */
            default:
            break;
        }
    }
    else
    {
    }

    return false;
}
