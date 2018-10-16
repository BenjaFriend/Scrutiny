/// <summary>
/// Testing grounds for the basics of Scrutiny
/// such as making sure the sockets are connecting properly,
/// checking for memory leaks, and performance testing. 
/// </summary>
/// <author>Ben Hoffman</author>


#include "stdafx.h"
#include "ScurintyExports.h"    // Export functions of scrutiny
#include <ctime>                // clock_t
#include <stdio.h>


void RunStressTest(Scrut::Scrutiny* aImpl, int aAmount)
{
	if (!aImpl) return;

    std::clock_t begin = clock();


	for (size_t i = 0; i < aAmount; ++i)
	{
		// Test a web request
        TestRequest(aImpl);
	}

    std::clock_t end = clock();
    double elapsed_secs = double( end - begin ) / CLOCKS_PER_SEC;

    printf( "\n\n\tElapsed time for %d tests is %f\n\n", aAmount, elapsed_secs );
}

int main()
{
// Enable memory leak detection
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Scrut::Scrutiny * s = CreateScrutiny("127.0.0.1", "9200");
    int result = 0;
    
    /*int amount = 30000;

    RunStressTest( s, amount );

    printf( "And now we can run it again probably\n\n" );

    RunStressTest( s, amount * 2 );*/

    float test = 10.568766f;
    
    StartReport( s );
    
    ReportFloat( s, "float_key", test );
    ReportFloat( s, "float_key_2", test / 2.f );
    ReportCharacter( s, "char_key", "this is a char key" );

    SendReport( s );

    result = TestRequest( s );
    //result = TestRequest( s );
    //result = TestRequest( s );

    DestroyScrutiny(s);
	
    //dump that info
#if defined(DEBUG) | defined(_DEBUG) 
    _CrtDumpMemoryLeaks();
#endif

	printf("\n\n\nPress Enter to exit...\n");
	getchar();
    return 0;
}
