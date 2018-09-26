#include "stdafx.h"
#include "HttpSocket.h"

#define DEFAULT_BUFLEN 1024

using namespace Scrut;

HttpSocket::HttpSocket(const char* aHostURL, const char* aHostPort)
{

	// Copy the host url and port into info
	strcpy_s(HostURL, strnlen_s(aHostURL, MAX_HOST_LENGTH) + 1, aHostURL);
	strcpy_s(HostPort, strnlen_s(aHostPort, MAX_HOST_LENGTH) + 1, aHostPort);

	// TODO: Create A socket here sockets
	// INitalize WinSoc
	WSADATA WsaDat;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		printf("WSA Initialization failed. Error Code : %d\n", WSAGetLastError());
		return;
	}

	strcpy_s(RequestHeader, MAX_REQUEST_LEN, " HTTP/1.1\r\n");
	
	strcat_s(RequestHeader, MAX_REQUEST_LEN, "Content-Type: application/json; charset=UTF-8\r\n");
	strcat_s(RequestHeader, MAX_REQUEST_LEN, "Content-Encoding: identity\r\n");
	strcat_s(RequestHeader, MAX_REQUEST_LEN, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36\r\n");
	strcat_s(RequestHeader, MAX_REQUEST_LEN, "Host: ");
	strcat_s(RequestHeader, MAX_REQUEST_LEN, " HTTP/1.1\r\n");
	strcat_s(RequestHeader, MAX_REQUEST_LEN, HostURL);
	strcat_s(RequestHeader, MAX_REQUEST_LEN, ":");
	strcat_s(RequestHeader, MAX_REQUEST_LEN, HostPort);
	strcat_s(RequestHeader, MAX_REQUEST_LEN, "\r\n");

}

HttpSocket::~HttpSocket()
{
	// Clean up the socket here	
	Disconnect();
}

int HttpSocket::ConnectSocket()
{
	int iResult = 0;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family		= AF_UNSPEC;
	hints.ai_socktype	= SOCK_STREAM;
	hints.ai_protocol	= IPPROTO_TCP;

	iResult = getaddrinfo(HostURL, HostPort, &hints, &result);

	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return iResult;
	}

	ptr = result;
	// Attempt to create a streaming socket using IP/TCP 
	Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	// Check for errors in the socket creation
	if (Socket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return iResult;
	}

	// Connect to server.
	iResult = connect(Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(Socket);
		Socket = INVALID_SOCKET;
		printf("-- Error with socket conn! --");
	}

	freeaddrinfo(result);

	if (Socket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return iResult;
	}

	return iResult;
}

int HttpSocket::SendRequest(const char* aMethod, const char* aIndexParam, const char* aMsg)
{
	// TODO: Make this a more effecient stream instead of using the std::string
	assert(strcmp(aMethod, "GET") || strcmp(aMethod, "POST") || strcmp(aMethod, "PUT") || strcmp(aMethod, "XDELETE"));
	
	// TODO: Investigate if I actually need to reconnect the socket every time a request is made? 
	ConnectSocket();

	// TODO: Make this more optimal by something with better insertion rates than an Array
	// Because strcat has to look for the null terminator every time, this is not a linear function
	char Request[MAX_REQUEST_LEN];
	strcpy_s(Request, MAX_REQUEST_LEN, aMethod);
	
	strcat_s(Request, MAX_REQUEST_LEN, " ");
	strcat_s(Request, MAX_REQUEST_LEN, aIndexParam);
	strcat_s(Request, MAX_REQUEST_LEN, RequestHeader);
	
	strcat_s(Request, MAX_REQUEST_LEN, "Content-Length: ");
	strcat_s(Request, MAX_REQUEST_LEN, std::to_string(strlen(aMsg)).c_str());
	strcat_s(Request, MAX_REQUEST_LEN, "\r\n");
	
	strcat_s(Request, MAX_REQUEST_LEN, ConnectionClose);
	strcat_s(Request, MAX_REQUEST_LEN, aMsg);
	strcat_s(Request, MAX_REQUEST_LEN, "\r\n");

	printf("\t\n========= REQUEST SENT\n\n%s \t\n========= End request send\n\n", Request);

	int iResult = 0;
	// Send an initial buffer
	iResult = send(Socket, Request, (int)strlen(Request), 0);
	if (iResult == SOCKET_ERROR) 
	{
		printf("send failed: %d\n", WSAGetLastError());
		Disconnect();
		return 1;
	}

	printf("\t\t ** Bytes Sent: %ld\n", iResult);

	// Receive data until the server closes the connection
	int BytesRecieved = 0;
	char RecieveBuffer[DEFAULT_BUFLEN];

	ZeroMemory(&RecieveBuffer, sizeof(RecieveBuffer));

	do 
	{
		// recieve data from the server's response
		// Using this socket, put the data we are reciving into the RecieveBuffer
		// until you get to this buffer length. 
		iResult = recv(Socket, RecieveBuffer, DEFAULT_BUFLEN, MSG_WAITALL);

		// Keep track of how much data we are recieing so that we can add a null terminator
		BytesRecieved += iResult;

	} while (iResult > 0);	// While we are getting a response from the server
	
	printf("\n\t\t ** Bytes Recieved: %d\n\n", BytesRecieved);

	// Add a null terminator to the end of the data we recieved
	RecieveBuffer[BytesRecieved] = 0;
	
	printf("\n============== Server Response:\n\n%s\n\n=============== End Server Response\n\n",  RecieveBuffer);
	
	
	return iResult;
}

void HttpSocket::Disconnect()
{
	if (Socket >= 0)
	{
		closesocket(Socket);
	}

	WSACleanup();
}