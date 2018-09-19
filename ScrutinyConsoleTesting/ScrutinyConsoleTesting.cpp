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

	//freopen("log.txt", "w", stdout);

	Scrut::Scrutiny * s = CreateScrutiny();

	int result = 0;
	// Test a web request
	result = TestRequest(s);
	//result = TestRequest(s);

	// Get the indecies in ELK
	//result = GetIndex(s, "/_cat/indices?v");

	// Get info about the twitter indecy
	//result = GetIndex(s, "/twitter/_doc");


	DestroyScrutiny(s);
	//fclose(stdout);

	printf("\n\n\nPress Enter to exit...\n");
	getchar();
    return 0;
}
