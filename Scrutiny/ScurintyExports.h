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

#endif  // SCRUTINY_EXPORTS


#include "Scrutiny.h"

Scrut::Scrutiny* Instance = nullptr;

extern "C"
{
    SCRUTINY_API void InitLib( const char* aServerAddress, const char* aServerPort );

    SCRUTINY_API void Release();

    SCRUTINY_API const int TestRequest();

    SCRUTINY_API const int GetIndex( const char* aIndex );

    SCRUTINY_API const int DeleteIndex( const char* aIndex );

    ////////////////////////////////////////////
    // Reporting methods

    SCRUTINY_API void StartReport();
    SCRUTINY_API const int SendReport();

    SCRUTINY_API void ReportFloat( const char* aKey, float aValue );
    SCRUTINY_API void ReportCharacter( const char* aKey, const char* aValue );
    SCRUTINY_API void ReportCustom( const char* aKey, CustomToStringDelegate aToStringFunc, void* funcArgs );
}