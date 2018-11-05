#pragma once

/// <summary>
/// Declare the functions that we need to export for the DLL
/// We need to do this for Unity to use it successfully.
/// </summary>
/// <author>Ben Hoffman</author>

// #MakeCrossPlatform
#ifdef SCRUTINY_EXPORTS
#define SCRUTINY_API __declspec(dllexport) 
#else
#define SCRUTINY_API __declspec(dllimport) 
#endif


#include "Scrutiny.h"

extern "C"
{
 
    SCRUTINY_API Scrut::Scrutiny* CreateScrutiny( const char* aServerAddress, const char* aServerPort );

    SCRUTINY_API void DestroyScrutiny( Scrut::Scrutiny* Impl );

    SCRUTINY_API const int TestRequest( Scrut::Scrutiny* Impl );

    SCRUTINY_API const int GetIndex( Scrut::Scrutiny* Impl, const char* aIndex );

    SCRUTINY_API const int DeleteIndex( Scrut::Scrutiny* Impl, const char* aIndex );

    ////////////////////////////////////////////
    // Reporting methods

    SCRUTINY_API void StartReport( Scrut::Scrutiny* Impl );
    SCRUTINY_API const int SendReport( Scrut::Scrutiny* Impl );

    SCRUTINY_API void ReportFloat( Scrut::Scrutiny* Impl, const char* aKey, float aValue );
    SCRUTINY_API void ReportCharacter( Scrut::Scrutiny* Impl, const char* aKey, const char* aValue );

}