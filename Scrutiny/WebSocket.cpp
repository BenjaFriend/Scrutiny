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
		Disconnect();
		return;
	}

	//printf("Our string is: \n\t");
	//printf(message.c_str());
	printf("\n\n ** Socket created ** \n");
}

WebSocket::~WebSocket()
{
	// Clean up the socket here	
	Disconnect();
}

int WebSocket::SendRequest(const char* aURL, const char* aMsg)
{
	// Use a socket to send this data to our ELK instance

	//printf("Request here! \n======\t\n %s \n\t %s\n======\n", aURL, aMsg);

	// This is the curl we want to replicate in winsoc
	// curl -X POST "localhost:9200/twitter/_doc/" -H 'Content-Type: application/json' -d
	// '{ "user" : "kimchy", "post_date" : "2018-09-13T14:12:12","message" : "trying out Elasticsearch FROM git bash" }'

	std::string post_http = "";
	post_http += "POST / HTTP/1.1\r\nHost: ";
	post_http += aURL;	// "127.0.0.1"
	post_http += "/twitter/_doc/";
	post_http += "\r\nConnection: close\r\n\r\n";
	post_http += "'{ \"user\" : \"kimchy\", ";
	post_http += "\"post_date\" : \"2017-09-13T14:12:12\", ";
	post_http += "\"message\" : \"trying out Elasticsearch FROM CPPPPP\" }'";

	printf("Our post message: \n\n%s\n\n", post_http.c_str());

	SOCKADDR_IN SockAddr;	// The address info of where we want to connect to
	//struct hostent *host;

	// SockAddr.sin_addr.s_addr = inet_addr( aURL );	// Use the specified server URL
	SockAddr.sin_port	= 9200;						// Port 9200 (Elasticsearch)
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
		Disconnect();
		return 1;
	}

	printf("\n\tSocket Connected!\n");	// we are failing here

	// Send a message to the server
	// use the above POST request to insert data into kibana
	send(Socket, post_http.c_str(), strlen(post_http.c_str()), 0);

	// Right now I don't care about what the response is

	printf("\nDone getting this stuff\n\n\n");
	return 0;
}

void WebSocket::Disconnect()
{
	if (Socket >= 0)
	{
		printf("\n\t***** Socket Closed *****\n");
		closesocket(Socket);
	}

	WSACleanup();
	printf("\n\t***** Socket Cleaned *****\n");

}