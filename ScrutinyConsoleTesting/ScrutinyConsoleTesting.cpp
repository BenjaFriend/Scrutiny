
#include "stdafx.h"
#include "Scrutiny.h"
#include "ScurintyExports.h"

int main()
{
	
	printf("This is a test!\n");

	Scrutiny* s = CreateScrutiny();

	DestroyScrutiny(s);

	printf("Press Enter to exit...");
	getchar();
    return 0;
}

