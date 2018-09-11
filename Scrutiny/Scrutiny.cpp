
#include "stdafx.h"
#include "Scrutiny.h"


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
	
	mySock.SendRequest("http://localhost:9200", "{ \"message\": \"This is a test message!\" } ");

	return 0;
}

// Define the functoins here
float Scrutiny::TestMultiply(float a, float b)
{
	return a * b;
}