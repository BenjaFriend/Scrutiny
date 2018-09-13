/**
*@ brief	Testing grounds for the basics of Scrutiny
* 
* @author	Ben Hoffman
*/

#include "stdafx.h"
#include "Scrutiny.h"
#include "ScurintyExports.h"

int main()
{
	Scrut::Scrutiny* s = CreateScrutiny();

	// Test a web request
	int result = TestRequest(s);

	DestroyScrutiny(s);


	printf("Press Enter to exit...");
	getchar();
    return 0;
}
