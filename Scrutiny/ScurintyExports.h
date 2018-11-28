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
    SCRUTINY_API void ReportCustom( Scrut::Scrutiny* Impl, const char* aKey, CustomToStringDelegate aToStringFunc, void* funcArgs );

    /*
    template <class T> SCRUTINY_API void ReportGeneric(
        Scrut::Scrutiny* Impl,
        const char* aKey,
        T* aVal,
        void( *toString_func )( char* aBuffer, size_t buf_size, T* aValue ) )
    {
        Impl->ReportGeneric( aKey, aVal, toString_func );
    }

    template void ReportGeneric<int>( 
        Scrut::Scrutiny* Impl,
        const char* aKey,
        int* aVal,
        void( *toString_func )( char* aBuffer, size_t buf_size, int* aValue ) 
        );
        */


}