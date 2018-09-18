#include "stdafx.h"
#include "WebSocket.h"

#define DEFAULT_BUFLEN 1024

using namespace Scrut;

WebSocket::WebSocket(const char* aHostURL, const char* aHostPort)
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


	ConnectSocket();

}

WebSocket::~WebSocket()
{
	// Clean up the socket here	
	Disconnect();
}

int WebSocket::ConnectSocket()
{
	int iResult = 0;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family		= AF_UNSPEC;
	hints.ai_socktype	= SOCK_STREAM;
	hints.ai_protocol	= IPPROTO_TCP;

	iResult = getaddrinfo(HostURL, "9200", &hints, &result);

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

int WebSocket::SendRequest(const char* aMethod, const char* aIndexParam, const char* aMsg)
{
	// This is the curl we want to replicate in winsoc
	// curl -X POST "localhost:9200/twitter/_doc/" -H 'Content-Type: application/json' -d
	// '{ "user" : "kimchy", "post_date" : "2018-09-13T14:12:12","message" : "trying out Elasticsearch FROM git bash" }'
	//post_http += "POST /twitter/_doc/1? HTTP/1.1\r\n";

	std::string body = "";
	//body += "{ \"post_date\" : \"2017-11-19T14:12:12\", ";
	//body += "\"message\" : \"trying out Elasticsearch FROM CPPPPP\" }";
	
	assert(strcmp(aMethod, "GET") || strcmp(aMethod, "POST") || strcmp(aMethod, "PUT"));

	std::string indexParam = aIndexParam;


	std::string post_http = "";
	post_http += aMethod;	// GET
	post_http += " " + indexParam;
	post_http += " HTTP/1.1\r\n";
	post_http += "Content-Type: application/json; charset=UTF-8\r\n";
	post_http += "Content-Encoding: identity\r\n";
	//post_http += "Content-Length: ";
	//post_http += std::to_string(body.length());	
	//post_http += "\r\n";

	post_http += "Host: ";
	post_http += HostURL;
	post_http += ":";
	post_http += HostPort;
	post_http += "\r\n";
	post_http += "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36\r\n";
	post_http += "Connection: close\r\n";
	post_http += "\r\n"; // EMPTY line between header and body.
	post_http += body;
	
	
	printf("Our request is here:\n=====\n\n%s\n=====\n", post_http.c_str());

	

	int iResult = 0;
	// Send an initial buffer
	iResult = send(Socket, post_http.c_str(), (int)strlen(post_http.c_str()), 0);
	if (iResult == SOCKET_ERROR) 
	{
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(Socket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %ld\n", iResult);

	/* ** NOTE ** 
	* This is the microsoft docs but it ends up cutting out the connection
	* to the server early when recieving ? 
	* shutdown the connection for sending since no more data will be sent
	* the client can still use the ConnectSocket for receiving data

	iResult = shutdown(Socket, SD_SEND);
	if (iResult == SOCKET_ERROR) 
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(Socket);
		WSACleanup();
		return 1;
	}*/

	// Receive data until the server closes the connection
	int dataRecieved = 0;
	char recvbuf[DEFAULT_BUFLEN];

	do 
	{
		iResult = recv(Socket, recvbuf, DEFAULT_BUFLEN, 0);
		dataRecieved += iResult;
		if (iResult > 0)
		{
			printf("Bytes received: %d\n", iResult);
		}
		else if (iResult == 0)
		{
			printf("Connection closed\n");
		}
		else
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
	} while (iResult > 0 /*&& dataRecieved <= DEFAULT_BUFLEN - 1*/);
	
	printf("\n\t\t ** Data Recieved: %d\n\n", dataRecieved);

	size_t length = strnlen_s(recvbuf, DEFAULT_BUFLEN);
	// Add a null terminator to the string
	recvbuf[dataRecieved] = 0;
	
	printf("Server Response:\n\n%s",  recvbuf);

	return iResult;
}

void WebSocket::Disconnect()
{
	if (Socket >= 0)
	{
		closesocket(Socket);
	}

	WSACleanup();
}