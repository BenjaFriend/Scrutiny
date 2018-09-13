#include "stdafx.h"
#include "WebSocket.h"

using namespace Scrut;

WebSocket::WebSocket()
{
	// Create some sockets
}

WebSocket::~WebSocket()
{
	// Destroy any info that we need to
}

void WebSocket::SendRequest(const char* aURL, const char* aMsg)
{
	// Use a socket to send this data to our ELK instance

	printf("Request here! \n\t %s \n\t %s", aURL, aMsg);


}
