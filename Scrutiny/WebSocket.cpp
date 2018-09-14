#include "stdafx.h"
#include "WebSocket.h"

using namespace Scrut;

WebSocket::WebSocket()
{
	// TODO: Create A socket here sockets
	// INitalize WinSoc
	WSADATA WsaDat;
	if (WSAStartup(MAKEWORD(1, 1), &WsaDat) != 0)
	{
		printf("WSA Initialization failed. Error Code : %d\n", WSAGetLastError());
		return;
	}
	printf("\n\n ** WSA Initialised. ** \n");

	// Attempt to create a streaming socket using IP/TCP 
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (Socket == INVALID_SOCKET)
	{
		printf("\nERROR: Socket creation failed.\n");
		// Cleanup this socket
		closesocket(Socket);
		WSACleanup();
		return;
	}

	//printf("Our string is: \n\t");
	//printf(message.c_str());
	printf("\n\n ** Socket created ** \n");
}

WebSocket::~WebSocket()
{
	// Clean up the socket here	
	closesocket(Socket);
	WSACleanup();
	printf("\n\t***** Socket Cleaned *****\n");
}

int WebSocket::SendRequest(const char* aURL, const char* aMsg)
{
	// Use a socket to send this data to our ELK instance

	printf("Request here! \n======\t %s \n\t %s\n======\n", aURL, aMsg);

	std::string message = "";
	message += "POST \"localhost:9200/twitter/_doc/\" -H 'Content-Type: application/json' -d'";
	message += "{ \"user\" : \"kimchy\", ";
	message += "\"post_date\" : \"2017-09-13T14:12:12\", ";
	message += "\"message\" : \"trying out Elasticsearch FROM CPPPPP\" }'";


	SOCKADDR_IN SockAddr;
	// SockAddr.sin_addr.s_addr = inet_addr( aURL );	// Use the specified server URL
	SockAddr.sin_port = 9200;						// Port 9200 (Elasticsearch)
	SockAddr.sin_family = AF_INET;					// we want TCP/IP
	
	// Connect to 127.0.0.1		
	//// TODO: Make this better obvi
	SockAddr.sin_addr.S_un.S_un_b.s_b1 = 127;
	SockAddr.sin_addr.S_un.S_un_b.s_b2 = 0;
	SockAddr.sin_addr.S_un.S_un_b.s_b3 = 0;
	SockAddr.sin_addr.S_un.S_un_b.s_b1 = 1;
	
	// Attempt to connect to the elk server
	if (connect(Socket, (SOCKADDR *)(&SockAddr), sizeof(SockAddr)) != 0)
	{
		printf("\n\tERROR: Failed to establish connection with server. Code %d\n", WSAGetLastError());
		// Cleanup this socket
		closesocket(Socket);
		WSACleanup();
		return 1;
	}

	printf("\n\tSocket Connected\n");	// we fail here

	// Send a message to the server
	// use the above POST request to insert data into kibana



	printf("\nDone getting this stuff\n\n\n");



	return 0;
}
