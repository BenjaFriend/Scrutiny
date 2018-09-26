#pragma once

/**
* @brief	Declare the functions that we need to export for the DLL
*			We need to do this for Unity to use it successfully.
*
* @author	Ben Hoffman
*/

#ifdef SCRUTINY_EXPORTS
#define SCRUTINY_API __declspec(dllexport) 
#else
#define SCRUTINY_API __declspec(dllimport) 
#endif


#include "Scrutiny.h"

extern "C"
{

	SCRUTINY_API Scrut::Scrutiny* CreateScrutiny(const char* aServerAddress, const char* aServerPort);

	SCRUTINY_API void DestroyScrutiny(Scrut::Scrutiny* Impl);

	SCRUTINY_API int TestRequest(Scrut::Scrutiny* Impl);

	SCRUTINY_API int GetIndex(Scrut::Scrutiny* Impl, const char* aIndex);

	SCRUTINY_API int DeleteIndex(Scrut::Scrutiny* Impl, const char* aIndex);

}