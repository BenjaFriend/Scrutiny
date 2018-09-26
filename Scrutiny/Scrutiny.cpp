
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
