/**
* @brief	Implementatoin of all exported functions. This has to 
*			be done with a pointer implementation because of 
*			limitations with Unity. 
* 
* @author	Ben Hoffman
*/

#include "stdafx.h"
#include "ScurintyExports.h"


extern "C"
{
	Scrut::Scrutiny* CreateScrutiny()
	{
		return new Scrut::Scrutiny();
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
}