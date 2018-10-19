// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <assert.h>		// assert macro
#include <stdlib.h>
#include <stdio.h>  

// TODO: reference additional headers your program requires here



#ifdef _DEBUG

#define DEBUG_PRINT(a, ...) printf("%s: %d " a "\n", __FILE__, __LINE__, __VA_ARGS__);

#else

#define DEBUG_PRINT(a, ...)

#endif