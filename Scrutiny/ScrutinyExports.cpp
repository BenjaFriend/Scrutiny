/**
* @brief	Implementatoin of all exported functions. This has to be done because
* 			of how Unity is working with their DLL import stuff
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

	float TestMultiply(Scrut::Scrutiny* Impl, float a, float b)
	{
		return Impl->TestMultiply(a, b);
	}


	int TestRequest(Scrut::Scrutiny* Impl)
	{
		return Impl->TestRequest();
	}
}