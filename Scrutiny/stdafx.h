

#pragma once

/************************************************************************/
/* Commonly used libraries                                              */
/************************************************************************/

#include <stdlib.h>  
#include <assert.h>


/************************************************************************/
/* Windows Specific                                                     */
/************************************************************************/
#if defined(_WIN32) || defined(_WIN64)

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#define _CRTDBG_MAP_ALLOC  

#ifdef _DEBUG
#include <crtdbg.h>  

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#endif

#endif      // WIN32 or WIN64


/************************************************************************/
/* Debug Settings                                                       */
/************************************************************************/

#ifdef _DEBUG

#define DEBUG_PRINT(a, ...) printf("%s: %d " a "\n", __FILE__, __LINE__, __VA_ARGS__);

#else

#define DEBUG_PRINT(a, ...)

#endif

typedef const char*( *CustomToStringDelegate )( void* );