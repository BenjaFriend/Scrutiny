#pragma once

/**
* @brief	Declare the functoins that we need to export for the DLL
*			We need to do this for Unity to use it sucesfully.
*
* @author	Ben Hoffman
*/

#ifdef SCRUTINYDLL_EXPORT
#define SCRUTINYDLL_API __declspec(dllexport) 
#else
#define SCRUTINYDLL_API __declspec(dllimport) 
#endif


#include "Scrutiny.h"

extern "C"
{

	// Constructor and Destructor for Scrutiny
	SCRUTINYDLL_API Scrut::Scrutiny* CreateScrutiny();
	SCRUTINYDLL_API void DestroyScrutiny(Scrut::Scrutiny* Impl);


	SCRUTINYDLL_API float TestMultiply(Scrut::Scrutiny* Impl, float a, float b);
	SCRUTINYDLL_API int TestRequest(Scrut::Scrutiny* Impl);


}