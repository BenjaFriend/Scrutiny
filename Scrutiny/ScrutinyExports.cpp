/// <summary>
/// implementation of all exported functions. This has to
/// be done with a pointer implementation because of  
/// limitations with Unity. 
/// </summary>
/// <author>Ben Hoffman</author>

#include "stdafx.h"
#include "ScurintyExports.h"

extern "C"
{
    void InitLib( const char * aServerAddress, const char * aServerPort )
    {
        assert( Instance == nullptr );

        Instance = new Scrut::Scrutiny( aServerAddress, aServerPort );
    }

    void Release()
    {
        if ( Instance != nullptr )
        {
            delete Instance;
        }
    }

    int const TestRequest()
    {
        assert( Instance != nullptr );

        return Instance->TestRequest();
    }

    int const GetIndex( const char* aIndex )
    {
        assert( Instance != nullptr );

        return Instance->GetIndex( aIndex );
    }

    int const DeleteIndex( const char * aIndex )
    {
        assert( Instance != nullptr );

        return Instance->DeleteIndex( aIndex );
    }

    ////////////////////////////////////////////
    // Reporting methods

    void StartReport()
    {
        assert( Instance != nullptr );

        return Instance->StartReport();
    }

    const int SendReport()
    {
        assert( Instance != nullptr );

        return Instance->SendReport();
    }

    void ReportFloat( const char* aKey, float aValue )
    {
        assert( Instance != nullptr );

        Instance->ReportFloat( aKey, aValue );
    }

    void ReportCharacter( const char* aKey, const char* aValue )
    {
        assert( Instance != nullptr );

        Instance->ReportCharacter( aKey, aValue );
    }

    void ReportCustom( const char* aKey, CustomToStringDelegate aToStringFunc, void* funcArgs )
    {
        assert( Instance != nullptr );

        Instance->ReportCustom( aKey, aToStringFunc, funcArgs );
    }

}