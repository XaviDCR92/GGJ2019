#ifndef SFX_HEADER__
#define SFX_HEADER__

#include <stdbool.h>
#include <psxspu.h>

/* *************************************
 *  Includes
 * *************************************/

/* *************************************
 *  Defines
 * *************************************/

#ifdef __cplusplus
#define EXTERNC extern "C"
#else /* __cplusplus */
#define EXTERNC
#endif /* __cplusplus */

 /* *************************************
 *  Structs and enums
 * *************************************/

/* *************************************
 *  Global prototypes
 * *************************************/
EXTERNC void SfxPlaySound(SsVag* sound);
EXTERNC bool SfxUploadSound(const char* const file_path, SsVag* const vag);

#endif //SFX_HEADER__
