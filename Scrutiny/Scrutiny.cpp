
#include "stdafx.h"
#include "Scrutiny.h"

using namespace Scrut;

Scrutiny::Scrutiny()
{
	printf("Scrutiny ctor");
}

Scrutiny::~Scrutiny()
{
	printf("scrutiny dtor");
}

int Scrutiny::TestRequest()
{
	printf("Test request!");
	WebSocket mySock;
	
	mySock.SendRequest("127.0.0.1", "{ \"message\": \"This is a test message!\" } ");

	return 0;
}

// Define the functoins here
float Scrutiny::TestMultiply(float a, float b)
{
	return a * b;
}