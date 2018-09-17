#include "stdafx.h"
#include "WebSocket.h"

#define DEFAULT_BUFLEN 512

using namespace Scrut;

WebSocket::WebSocket()
{
	// TODO: Create A socket here sockets
	// INitalize WinSoc
	WSADATA WsaDat;
	if (WSAStartup(MAKEWORD(2, 2), &WsaDat) != 0)
	{
		printf("WSA Initialization failed. Error Code : %d\n", WSAGetLastError());
		return;
	}
}

WebSocket::~WebSocket()
{
	// Clean up the socket here	
	Disconnect();
}

int WebSocket::SendRequest(const char* aURL, const char* aMsg)
{
	// This is the curl we want to replicate in winsoc
	// curl -X POST "localhost:9200/twitter/_doc/" -H 'Content-Type: application/json' -d
	// '{ "user" : "kimchy", "post_date" : "2018-09-13T14:12:12","message" : "trying out Elasticsearch FROM git bash" }'

	std::string body = "";
	body += "{ \"post_date\" : \"2017-11-16T14:12:12\", ";
	body += "\"message\" : \"trying out Elasticsearch FROM CPPPPP\" }";
	
	std::string url = aURL;

	std::string post_http = "";
	post_http += "POST /twitter/_doc/1? HTTP/1.1\r\n";
	post_http += "Content-Type: application/json; charset=UTF-8\r\n";
	post_http += "Content-Encoding: identity\r\n";
	post_http += "Content-Length: ";
	post_http += std::to_string(body.length());	
	post_http += "\r\n";
	post_http += "Host: " + url + ":9200\r\n";
	post_http += "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36\r\n";
	post_http += "Connection: close\r\n";
	post_http += "\r\n"; // EMPTY line between header and body.
	post_http += body;
	
	
	printf("Our request is here:\n=====\n\n%s\n=====\n", post_http.c_str());

	int iResult = 0;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("127.0.0.1", "9200", &hints, &result);

	if (iResult != 0)
	{
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
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
		return 1;
	}

	// Connect to server.
	iResult = connect(Socket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) 
	{
		closesocket(Socket);
		Socket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (Socket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	int recvbuflen = DEFAULT_BUFLEN;
	char recvbuf[DEFAULT_BUFLEN];

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

	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(Socket, SD_SEND);
	if (iResult == SOCKET_ERROR) 
	{
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(Socket);
		WSACleanup();
		return 1;
	}

	// Receive data until the server closes the connection
	int dataRecieved = 0;
	do 
	{
		iResult = recv(Socket, recvbuf, recvbuflen, 0);
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
	} while (iResult > 0);
	
	recvbuf[ dataRecieved ] = 0;
	
	printf("Server Response:\n\n%s",  recvbuf);

	return 0;
}

void WebSocket::Disconnect()
{
	if (Socket >= 0)
	{
		closesocket(Socket);
	}

	WSACleanup();
}