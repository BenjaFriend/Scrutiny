
#include "stdafx.h"
#include "Scrutiny.h"

using namespace Scrut;

Scrutiny::Scrutiny()
{

}

Scrutiny::~Scrutiny()
{

}

int Scrutiny::TestRequest()
{
	WebSocket mySock;
	
	mySock.SendRequest("127.0.0.1", "{ \"message\": \"This is a test message!\" } ");

	return 0;
}

// Define the functoins here
float Scrutiny::TestMultiply(float a, float b)
{
	return a * b;
}