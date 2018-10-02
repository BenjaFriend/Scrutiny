
#include "stdafx.h"
#include "Scrutiny.h"

using namespace Scrut;

Scrutiny::Scrutiny()
{
	ELK_Socket = new HttpSocket("127.0.0.1", "9200");


	// Enable memory leak detection
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

}

Scrutiny::Scrutiny(const char* aServerAddress, const char* aServerPort)
{
	// Enable memory leak detection
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ELK_Socket = new HttpSocket(aServerAddress, aServerPort);
}

Scrutiny::~Scrutiny()
{
	if (ELK_Socket) delete ELK_Socket;
}

int Scrutiny::TestRequest()
{
	return ELK_Socket->SendRequest(
		POST,
		"/twitter/_doc/",
		"{ \"user\" : \"kimchy\", \"post_date\" : \"2018-09-16T14:12:12\", \"message\" : \"trying out Elasticsearch FROM c++ BOII\" }"
	);
}

int Scrutiny::GetIndex(const char * index)
{
	return ELK_Socket->SendRequest(GET, index, "");
}

int Scrut::Scrutiny::DeleteIndex(const char* aIndex)
{
	return (
		ELK_Socket->SendRequest(
		XDELETE,
		aIndex,
		""
		)
	);

}

char* Scrut::Scrutiny::GetCurrentTimeFormat( char* aOutArray )
{
    struct tm newtime;
    char am_pm[] = "AM";
    __time64_t long_time;
    char timebuf[ 26 ];
    errno_t err;

    // Get time as 64-bit integer.  
    _time64( &long_time );
    // Convert to local time.  
    err = _localtime64_s( &newtime, &long_time );
    if ( err )
    {
        printf( "Invalid argument to _localtime64_s." );
    }
    if ( newtime.tm_hour > 12 )        // Set up extension.   
        strcpy_s( am_pm, sizeof( am_pm ), "PM" );
    if ( newtime.tm_hour > 12 )        // Convert from 24-hour   
        newtime.tm_hour -= 12;    // to 12-hour clock.   
    if ( newtime.tm_hour == 0 )        // Set hour to 12 if midnight.  
        newtime.tm_hour = 12;
    
    // Convert to an ASCII representation.   
    err = asctime_s( timebuf, 26, &newtime );
    if ( err )
    {
        printf( "Invalid argument to asctime_s." );
    }

    printf( "%.19s %s\n", timebuf, am_pm );
    
    char buf[ 32 ];

    // Year
    _itoa_s( newtime.tm_year + 1900, buf, 10 );
    strcat_s( aOutArray, 32, buf );
    strcat_s( aOutArray, 32, "-" );

    // Month
    _itoa_s( newtime.tm_mon + 1, buf, 10 );
    if ( newtime.tm_mon + 1 < 10 )
        strcat_s( aOutArray, 32, "0" );

    strcat_s( aOutArray, 32, buf );
    strcat_s( aOutArray, 32, "-" );

    // Day
    _itoa_s( newtime.tm_mday, buf, 10 );

    if ( newtime.tm_mday < 10 )
        strcat_s( aOutArray, 32, "0" );

    strcat_s( aOutArray, 32, buf );
    strcat_s( aOutArray, 32, "T" );

    // Hour
    _itoa_s( newtime.tm_hour, buf, 10 );
    strcat_s( aOutArray, 32, buf );
    strcat_s( aOutArray, 32, ":" );

    // Min
    _itoa_s( newtime.tm_min, buf, 10 );
    strcat_s( aOutArray, 32, buf );
    strcat_s( aOutArray, 32, ":" );

    // Sec
    _itoa_s( newtime.tm_sec, buf, 10 );

    if(newtime.tm_sec < 10 )
        strcat_s( aOutArray, 32, "0" );

    strcat_s( aOutArray, 32, buf );
    // Add the null term
    strcat_s( aOutArray, 32, "\0" );

    printf( "This time: \t%s\n\n", aOutArray );
    
    return aOutArray;
}
