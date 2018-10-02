/**
* @brief	Implementation of all exported functions. This has to 
*			be done with a pointer implementation because of 
*			limitations with Unity. 
* 
* @author	Ben Hoffman
*/

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

	int TestRequest(Scrut::Scrutiny* Impl)
	{
		return Impl->TestRequest();
	}

	int GetIndex(Scrut::Scrutiny* Impl, const char* aIndex)
	{
		return Impl->GetIndex(aIndex);
	}

	int DeleteIndex(Scrut::Scrutiny * Impl, const char * aIndex)
	{
		return Impl->DeleteIndex(aIndex);
	}
}