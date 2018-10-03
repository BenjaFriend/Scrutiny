/// <summary>
/// Implementation of all exported functions. This has to
/// be done with a pointer implementation because of  
/// limitations with Unity. 
/// </summary>
/// <author>Ben Hoffman</author>

#include "stdafx.h"
#include "ScurintyExports.h"

extern "C"
{

	Scrut::Scrutiny * CreateScrutiny(const char * aServerAddress, const char * aServerPort)
	{
		return new Scrut::Scrutiny(aServerAddress, aServerPort);
	}

	void DestroyScrutiny(Scrut::Scrutiny* Impl)
	{
		delete Impl;
	}

	int const TestRequest(Scrut::Scrutiny* Impl)
	{
		return Impl->TestRequest();
	}

	int const GetIndex(Scrut::Scrutiny* Impl, const char* aIndex)
	{
		return Impl->GetIndex(aIndex);
	}

	int const DeleteIndex(Scrut::Scrutiny * Impl, const char * aIndex)
	{
		return Impl->DeleteIndex(aIndex);
	}

    ////////////////////////////////////////////
    // Reporting methods

    void StartReport( Scrut::Scrutiny* Impl )
    {
        return Impl->StartReport();
    }

    const int SendReport( Scrut::Scrutiny* Impl )
    {
        return Impl->SendReport();
    }

    void ReportFloat( Scrut::Scrutiny* Impl, const char* aKey, float aValue )
    {
        Impl->ReportFloat( aKey, aValue );
    }

    void ReportCharacter( Scrut::Scrutiny* Impl, const char* aKey, const char* aValue )
    {
        Impl->ReportCharacter( aKey, aValue );
    }

}