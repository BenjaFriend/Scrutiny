
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

char* Scrut::Scrutiny::GetCurrentTimeFormat()
{
    const std::time_t t = std::time( 0 );

    //std::tm* now = std::localtime_s( &t );
    int h = ( t / 360 ) % 24 ;
    int m = ( t / 60 ) % 60;
    int s = t % 60;

    //printf( "UTC:       %s\n", asctime( gmtime( &t ) ) );
    //printf( "local:     %s\n", asctime( localtime( &t ) ) );

    printf( "Date : %02d:%02d:%02d\n", h, m, s );
    
    return nullptr;
}

/*
public string GenerateTimeStamp()
{
    return
    DateTime.Today.Year.ToString() + "-" +
    DateTime.Today.ToString("MM") + "-" +
    DateTime.Today.ToString("dd") +
    "T" + DateTime.Now.ToString("hh") + ":" +
    DateTime.Now.ToString("mm") + ":" +
    DateTime.Now.ToString("ss") + ".000Z";
}
*/