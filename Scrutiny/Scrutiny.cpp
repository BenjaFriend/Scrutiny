
#include "stdafx.h"
#include "Scrutiny.h"


using namespace Scrut;

Scrutiny::Scrutiny( const char* aServerAddress, const char* aServerPort )
{
    // Enable memory leak detection
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    ELK_Socket = new HttpSocket( aServerAddress, aServerPort );

    CurrentIndex = new char[ TIME_BUF_SIZE ];
    strcpy_s( CurrentIndex, 64, "/test.index/_doc/\0" );

    CurrentRequest = new char[ REQUEST_LEN ];
    CurrentRequest[ 0 ] = '\0';
}

Scrutiny::~Scrutiny()
{
    if ( ELK_Socket )
    {
        delete ELK_Socket;
        ELK_Socket = nullptr;
    }

    if ( CurrentIndex )
    {
        delete[] CurrentIndex;
        CurrentIndex = nullptr;
    }

    if ( CurrentRequest )
    {
        delete[] CurrentRequest;
        CurrentRequest = nullptr;
    }
}

const int Scrutiny::TestRequest()
{
    StartReport();
    float test = 17.0f;

    ReportFloat( "float_key", test );
    ReportFloat( "float_key_2", test / 2.f );
    ReportCharacter( "char_key", "this is a char key" );

    return SendReport();
}

void Scrutiny::StartReport()
{
    // Creates the current request
    strcpy_s( CurrentRequest, 512, "{ \"post_date\" : \"" );
    AppendCurrentTimeFormat( CurrentRequest );
}

const int Scrutiny::SendReport()
{
    strcat_s( CurrentRequest, 512, " }" );

    return ELK_Socket->SendRequest( POST, CurrentIndex, CurrentRequest );
}

void Scrutiny::ReportFloat( const char * aKey, float aValue )
{
    SetKey( aKey );

    char buf[ _CVTBUFSIZE ];
    _gcvt_s( buf, _CVTBUFSIZE, aValue, 5 );

    strcat_s( CurrentRequest, REQUEST_LEN, buf );
    strcat_s( CurrentRequest, REQUEST_LEN, "\"" );
}

void Scrutiny::ReportCharacter( const char* aKey, const char* aVal )
{
    SetKey( aKey );

    strcat_s( CurrentRequest, REQUEST_LEN, aVal );
    strcat_s( CurrentRequest, REQUEST_LEN, "\"" );
}

void Scrutiny::ReportCustom( const char* aKey, CustomToStringDelegate customFunc, void* funcArgs )
{
    SetKey( aKey );

    strcat_s( CurrentRequest, REQUEST_LEN, customFunc( funcArgs ) );

    strcat_s( CurrentRequest, REQUEST_LEN, "\"" );

}

void Scrutiny::SetKey( const char* aKey )
{
    strcat_s( CurrentRequest, REQUEST_LEN, ", \"" );
    strcat_s( CurrentRequest, REQUEST_LEN, aKey );
    strcat_s( CurrentRequest, REQUEST_LEN, "\": \"" );
}

const int Scrutiny::GetIndex( const char * index ) const
{
    return ELK_Socket->SendRequest( GET, index, "" );
}

const int Scrutiny::DeleteIndex( const char* aIndex ) const
{
    return (
        ELK_Socket->SendRequest(
            XDELETE,
            aIndex,
            ""
        )
        );
}

const char* Scrutiny::AppendCurrentTimeFormat( char* aOutArray )
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
    if ( newtime.tm_hour == 0 )        // Set hour to 12 if midnight.  
        newtime.tm_hour = 12;

    // Convert to an ASCII representation.   
    err = asctime_s( timebuf, 26, &newtime );
    if ( err )
    {
        printf( "Invalid argument to asctime_s." );
    }

    char buf[ 64 ];

    // Year
    _itoa_s( newtime.tm_year + 1900, buf, 10 );
    strcat_s( aOutArray, TIME_BUF_SIZE, buf );
    strcat_s( aOutArray, TIME_BUF_SIZE, "-" );

    // Month
    _itoa_s( newtime.tm_mon + 1, buf, 10 );
    if ( newtime.tm_mon + 1 < 10 )
        strcat_s( aOutArray, TIME_BUF_SIZE, "0" );

    strcat_s( aOutArray, TIME_BUF_SIZE, buf );
    strcat_s( aOutArray, TIME_BUF_SIZE, "-" );

    // Day
    _itoa_s( newtime.tm_mday, buf, 10 );

    if ( newtime.tm_mday < 10 )
        strcat_s( aOutArray, TIME_BUF_SIZE, "0" );

    strcat_s( aOutArray, TIME_BUF_SIZE, buf );
    strcat_s( aOutArray, TIME_BUF_SIZE, "T" );

    // Hour
    _itoa_s( newtime.tm_hour, buf, 10 );
    strcat_s( aOutArray, TIME_BUF_SIZE, buf );
    strcat_s( aOutArray, TIME_BUF_SIZE, ":" );

    // Min
    _itoa_s( newtime.tm_min, buf, 10 );
    if ( newtime.tm_min < 10 )
        strcat_s( aOutArray, TIME_BUF_SIZE, "0" );

    strcat_s( aOutArray, TIME_BUF_SIZE, buf );
    strcat_s( aOutArray, TIME_BUF_SIZE, ":" );

    // Sec
    _itoa_s( newtime.tm_sec, buf, 10 );

    if ( newtime.tm_sec < 10 )
        strcat_s( aOutArray, TIME_BUF_SIZE, "0" );

    strcat_s( aOutArray, TIME_BUF_SIZE, buf );
    // Add the null term
    strcat_s( aOutArray, TIME_BUF_SIZE, "\"\0" );


    return aOutArray;
}

/////////////////////////////////////////////////////////////////
// Accessors

const char* Scrutiny::GetCurrentIndex() const
{
    return CurrentIndex;
}

const char* Scrutiny::GetCurrentRequest() const
{
    return CurrentRequest;
}