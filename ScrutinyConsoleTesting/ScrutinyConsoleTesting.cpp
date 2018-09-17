/**
*@ brief	Testing grounds for the basics of Scrutiny
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

	// Test a web request
	int result = TestRequest(s);

	DestroyScrutiny(s);


	printf("\n\nPress Enter to exit...\n");
	getchar();
    return 0;
}
