/**
* @brief	Testing grounds for the basics of Scrutiny 
*			like making sure the sockets work, checking for 
*			memory leaks, etc. 
* 
* @author	Ben Hoffman
*/

#include "stdafx.h"
#include "ScurintyExports.h"


void RunStressTest(Scrut::Scrutiny* aImpl)
{
	if (!aImpl) return;

	for (size_t i = 0; i < 500000; ++i)
	{
		// Test a web request
		TestRequest(aImpl);
	}
}

int main()
{
// Enable memory leak detection
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Scrut::Scrutiny * s = CreateScrutiny("127.0.0.1", "9200");

	int result = 0;


    //RunStressTest(s);

    result = TestRequest( s );
    //result = TestRequest( s );
    //result = TestRequest( s );

	//DeleteIndex(s, "twitter");

	// Get the indices in ELK
	//result = GetIndex(s, "/_cat/indices?v");

	// Get info about the twitter index
	//result = GetIndex(s, "/twitter");


	DestroyScrutiny(s);
	
	printf("\n\n\nPress Enter to exit...\n");
	getchar();
    return 0;
}
