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
	
	Scrutiny* CreateScrutiny()
	{
		return new Scrutiny();
	}

	void DestroyScrutiny(Scrutiny* Impl)
	{
		delete Impl;
	}

	float TestMultiply(Scrutiny* Impl, float a, float b)
	{
		return Impl->TestMultiply(a, b);
	}


	int TestRequest(Scrutiny* Impl)
	{
		return Impl->TestRequest();
	}
}