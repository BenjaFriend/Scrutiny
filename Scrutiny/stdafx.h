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
#include <stdio.h>  

// TODO: reference additional headers your program requires here
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#include <assert.h>
// Replace the new keyword with the debug new 
#ifdef _DEBUG

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#endif


#ifdef _DEBUG

#define DEBUG_PRINT(a, ...) printf("%s: %d " a "\n", __FILE__, __LINE__, __VA_ARGS__);

#else

#define DEBUG_PRINT(a, ...)

#endif