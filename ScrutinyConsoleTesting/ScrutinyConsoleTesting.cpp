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


struct Vector
{
    float x;
    float y;
    float z;

    void TestMemberFunc( char* aRequest_Buffer, size_t buf_size, Vector* aVal )
    {
        if ( buf_size < sizeof( Vector ) ) return;

        // Add the X
        char floatBuf [ _CVTBUFSIZE ];
        _gcvt_s( floatBuf, _CVTBUFSIZE, aVal->x, 5 );
        strcat_s( aRequest_Buffer, buf_size, floatBuf );
        strcat_s( aRequest_Buffer, buf_size, " : " );

        // Add the Y
        char floatBuf2 [ _CVTBUFSIZE ];
        _gcvt_s( floatBuf2, _CVTBUFSIZE, aVal->y, 5 );
        strcat_s( aRequest_Buffer, buf_size, floatBuf2 );
        strcat_s( aRequest_Buffer, buf_size, " : " );

        // Add the Z
        char floatBuf3 [ _CVTBUFSIZE ];

        _gcvt_s( floatBuf3, _CVTBUFSIZE, aVal->z, 5 );
        strcat_s( aRequest_Buffer, buf_size, floatBuf3 );
        strcat_s( aRequest_Buffer, buf_size, " : " );

    }
};

void TestPrintFunc( char* aRequest_Buffer, size_t buf_size, Vector* aVal )
{
    if ( buf_size < sizeof( Vector ) ) return;

    // Add the X
    char floatBuf [ _CVTBUFSIZE ];
    _gcvt_s( floatBuf, _CVTBUFSIZE, aVal->x, 5 );
    strcat_s( aRequest_Buffer, buf_size, floatBuf );
    strcat_s( aRequest_Buffer, buf_size, " : " );

    // Add the Y
    char floatBuf2 [ _CVTBUFSIZE ];
    _gcvt_s( floatBuf2, _CVTBUFSIZE, aVal->y, 5 );
    strcat_s( aRequest_Buffer, buf_size, floatBuf2 );
    strcat_s( aRequest_Buffer, buf_size, " : " );

    // Add the Z
    char floatBuf3 [ _CVTBUFSIZE ];

    _gcvt_s( floatBuf3, _CVTBUFSIZE, aVal->z, 5 );
    strcat_s( aRequest_Buffer, buf_size, floatBuf3 );
    strcat_s( aRequest_Buffer, buf_size, " : " );

}

void RunStressTest( Scrut::Scrutiny* aImpl, int aAmount )
{
    if ( !aImpl ) return;

    std::clock_t begin = clock();


    for ( size_t i = 0; i < aAmount; ++i )
    {
        // Test a web request
        TestRequest();
    }

    std::clock_t end = clock();
    double elapsed_secs = double( end - begin ) / CLOCKS_PER_SEC;

    printf( "\n\n\tElapsed time for %d tests is %f\n\n", aAmount, elapsed_secs );
}

int main()
{
    // Enable memory leak detection
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    InitLib( "127.0.0.1", "9200" );
    int result = 0;

    /*int amount = 30000;

    RunStressTest( s, amount );

    printf( "And now we can run it again probably\n\n" );

    RunStressTest( s, amount * 2 );*/

    Vector v = { 1.15f, 2.0f, 3.5f };

    //char fake_request[ 64 ] = {};
    //TestPrintFunc( fake_request, 64, &v );
    //printf( "Resulting request: \n %s\n", fake_request );

    float test = 10.568766f;

    StartReport();

    //ReportCustom( "generic_key", &TestPrintFunc, &v );

    //ReportCustom( "generic_key_member", &v, &Vector::TestMemberFunc );

    ReportFloat( "float_key", test );
    ReportFloat( "float_key_2", test / 2.f );
    ReportCharacter( "char_key", "this is a char key" );
    ReportCharacter( "Language", "C++" );

    SendReport();


    // sEND a second test
    StartReport();

    //ReportGeneric( "generic_key", &v, &TestPrintFunc );

    ReportFloat( "float_key", test );
    ReportFloat( "float_key_2", test / 2.f );
    ReportCharacter( "char_key", "this is a char key" );

    SendReport();

    //result = TestRequest( s );
    //result = TestRequest( s );
    //result = TestRequest( s );



    Release();



    //dump that info
#if defined(DEBUG) | defined(_DEBUG) 
    _CrtDumpMemoryLeaks();
#endif


    return 0;
}
