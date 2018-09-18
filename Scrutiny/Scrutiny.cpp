
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
	ELK_Socket->SendRequest("GET", "/twitter/_doc/0", "{ \"message\": \"This is a test message!\" } ");

	return 0;
}

int Scrutiny::GetIndex(const char * index)
{
	return ELK_Socket->SendRequest("GET", index, "{ \"message\": \"This is a test message!\" } ");
}
