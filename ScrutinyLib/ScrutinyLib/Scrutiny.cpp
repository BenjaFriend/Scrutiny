#include "stdafx.h"
#include "Scrutiny.h"


Scrutiny::Scrutiny()
{
	printf("Scrutiny ctor");
}


Scrutiny::~Scrutiny()
{
	printf("Scrutiny dcor");
}

float Scrutiny::TestMultiply(float a, float b)
{
	return a * b;
}
