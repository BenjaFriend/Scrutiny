/**
* @brief	Testing grounds for the basics of Scrutiny 
*			like making sure the sockets work, checking for 
*			memroy leaks, etc. 
* 
* @author	Ben Hoffman
*/

#include "stdafx.h"
#include "Scrutiny.h"
#include "ScurintyExports.h"

int main()
{
// Enable memory leak detetction
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Scrut::Scrutiny * s = CreateScrutiny();

	int result = 0;

	/*for (size_t i = 0; i < 500000; ++i)
	{
		// Test a web request
		result = TestRequest(s);
	}*/

	// Test a web request
	result = TestRequest(s);

	// Get the indecies in ELK
	//result = GetIndex(s, "/_cat/indices?v");

	// Get info about the twitter indecy
	//result = GetIndex(s, "/twitter");


	DestroyScrutiny(s);
	
	printf("\n\n\nPress Enter to exit...\n");
	getchar();
    return 0;
}
