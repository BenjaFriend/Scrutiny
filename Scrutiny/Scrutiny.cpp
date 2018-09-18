
#include "stdafx.h"
#include "Scrutiny.h"

using namespace Scrut;

Scrutiny::Scrutiny()
{
	ELK_Socket = new WebSocket("127.0.0.1", "9200");
}

Scrutiny::~Scrutiny()
{
	if (ELK_Socket) delete ELK_Socket;
}

int Scrutiny::TestRequest()
{
	// TODO: Setup the message portion of this to be auto formatted with a JSON parser
	ELK_Socket->SendRequest(
		"POST",
		"/twitter/_doc/", 
		"{ \"user\" : \"kimchy\", \"post_date\" : \"2017-11-13T14:12:12\", \"message\" : \"trying out Elasticsearch FROM c++ BOII\" }"
	);

	return 0;
}

int Scrutiny::GetIndex(const char * index)
{
	return ELK_Socket->SendRequest("GET", index, "");
}
