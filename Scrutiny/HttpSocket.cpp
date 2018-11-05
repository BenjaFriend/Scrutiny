#include "stdafx.h"
#include "HttpSocket.h"

using namespace Scrut;

HttpSocket::HttpSocket( const char* aHostURL, const char* aHostPort )
{

    // Copy the host url and port into info
    strcpy_s( HostURL, strnlen_s( aHostURL, MAX_HOST_LENGTH ) + 1, aHostURL );
    strcpy_s( HostPort, strnlen_s( aHostPort, MAX_HOST_LENGTH ) + 1, aHostPort );

    // TODO: Create A socket here sockets
    // INitalize WinSoc
    WSADATA WsaDat;
    if ( WSAStartup( MAKEWORD( 2, 2 ), &WsaDat ) != 0 )
    {
        printf( "WSA Initialization failed. Error Code : %d\n", WSAGetLastError() );
        return;
    }

    DEBUG_PRINT("Test method boi %s : %d", "Hello?", 2 )

    InitHeaders();

    ConnectSocket( SendSocket );
    ConnectSocket( RecieveSocket );

    isDone = false;

    // Start a receive thread
    //Recieve_Thread = std::thread( &HttpSocket::RecieveThread, this );

}

HttpSocket::~HttpSocket()
{
    // Clean up the socket here	
    Disconnect();

    // Wait for the receive thread to be done
    isDone = true;
    RecieveDataCondition.notify_all();
    /*if ( Recieve_Thread.joinable() )
    {
        Recieve_Thread.join();
    }*/
}

const int HttpSocket::ConnectSocket( SOCKET& aSoc )
{
    int iResult = 0;

    struct addrinfo *result = NULL,
        *ptr = NULL,
        hints;

    ZeroMemory( &hints, sizeof( hints ) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo( HostURL, HostPort, &hints, &result );

    if ( iResult != 0 )
    {
        printf( "getaddrinfo failed: %d\n", iResult );
        WSACleanup();
        return iResult;
    }

    ptr = result;
    // Attempt to create a streaming socket using IP/TCP 
    aSoc = socket( ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol );
    // Check for errors in the socket creation
    if ( aSoc == INVALID_SOCKET )
    {
        printf( "Error at socket(): %ld\n", WSAGetLastError() );
        freeaddrinfo( result );
        WSACleanup();
        return iResult;
    }
    
    // Connect to server.
    iResult = connect( aSoc, ptr->ai_addr, (int) ptr->ai_addrlen );
    if ( iResult == SOCKET_ERROR )
    {
        closesocket( aSoc );
        aSoc = INVALID_SOCKET;
        printf( "-- Error with socket conn! --" );
    }

    freeaddrinfo( result );

    if ( aSoc == INVALID_SOCKET )
    {
        printf( "Unable to connect to server!\n" );
        WSACleanup();
        return iResult;
    }

    return iResult;
}

void HttpSocket::InitHeaders()
{
    strcpy_s( RequestHeader, MAX_REQUEST_LEN, " HTTP/1.1\r\n" );

    strcat_s( RequestHeader, MAX_REQUEST_LEN, "Content-Type: application/json; charset=UTF-8\r\n" );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, "Content-Encoding: identity\r\n" );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36\r\n" );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, "Host: " );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, " HTTP/1.1\r\n" );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, HostURL );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, ":" );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, HostPort );
    strcat_s( RequestHeader, MAX_REQUEST_LEN, "\r\n" );

}

const int HttpSocket::SendRequest( const char* aMethod, const char* aIndexParam, const char* aMsg )
{
    assert( strcmp( aMethod, "GET" ) || strcmp( aMethod, "POST" ) || strcmp( aMethod, "PUT" ) || strcmp( aMethod, "XDELETE" ) );

    ConnectSocket( SendSocket );

    char Request[ MAX_REQUEST_LEN ];
    char* reqPtr = Request;

    Request[ 0 ] = '\0';

    reqPtr = StrCat_NoCheck( reqPtr, aMethod );

    reqPtr = StrCat_NoCheck( reqPtr, " " );
    reqPtr = StrCat_NoCheck( reqPtr, aIndexParam );
    reqPtr = StrCat_NoCheck( reqPtr, RequestHeader );

    reqPtr = StrCat_NoCheck( reqPtr, "Content-Length: " );
    reqPtr = StrCat_NoCheck( reqPtr, std::to_string( strlen( aMsg ) ).c_str() );
    reqPtr = StrCat_NoCheck( reqPtr, "\r\n" );

    reqPtr = StrCat_NoCheck( reqPtr, ConnectionClose );
    reqPtr = StrCat_NoCheck( reqPtr, aMsg );
    reqPtr = StrCat_NoCheck( reqPtr, "\r\n" );

    int iResult = 0;

    DEBUG_PRINT( "\t\n========= REQUEST SENT\n\n%s \t\n========= End request send\n\n", Request );

    // Send an initial buffer
    iResult = send( SendSocket, Request, (int) strlen( Request ), 0 );
    if ( iResult == SOCKET_ERROR )
    {
        DEBUG_PRINT( "send failed: %d\n", WSAGetLastError() );
        Disconnect();
        return 1;
    }

    DEBUG_PRINT( "\t\t ** Bytes Sent: %ld\n", iResult );

    // Let the recv thread know that we want to listen!
    RecieveDataCondition.notify_one();

    // I don't _acutally_ need to be waiting for a response from the server for
    // just sending analytics. This will be a lot more preform ant than 
    // waiting for the response 

    RecvData();

    return iResult;
}

const int Scrut::HttpSocket::RecvData()
{
    int iResult = 0;
    ConnectSocket( RecieveSocket );

    // Receive data until the server closes the connection
    int BytesRecieved = 0;
    char RecieveBuffer[ MAX_RECV_BUF_LEN ];

    ZeroMemory( &RecieveBuffer, sizeof( RecieveBuffer ) );

    do
    {
        // receive data from the server's response
        iResult = recv( RecieveSocket, RecieveBuffer, MAX_RECV_BUF_LEN, MSG_WAITALL );

        // Keep track of how much data we are receive so that we can add a null terminator
        BytesRecieved += iResult;

    } while ( iResult > 0 );	// While we are getting a response from the server

    DEBUG_PRINT("\n\t\t ** Bytes Received: %d\n\n", BytesRecieved);

    // Add a null terminator to the end of the data we received
    //RecieveBuffer[ BytesRecieved ] = 0;

    DEBUG_PRINT("\n============== Server Response:\n\n%s\n\n=============== End Server Response\n\n",  RecieveBuffer);


    return iResult;
}

void HttpSocket::Disconnect()
{
    if ( SendSocket >= 0 )
    {
        closesocket( SendSocket );
    }

    if ( RecieveSocket >= 0 )
    {
        closesocket( RecieveSocket );
    }

    WSACleanup();
}

// Because strcat has to look for the null terminator every time, this is not a linear function
// This StrCat_NoCheck function is a linear function
char * Scrut::HttpSocket::StrCat_NoCheck( char * aDest, const char * aSrc )
{
    while ( *aDest ) aDest++;
    while ( *aDest++ = *aSrc++ );
    return --aDest;
}

void Scrut::HttpSocket::RecieveThread()
{
    printf( "Enter the Receive thread!\n" );

    std::unique_lock<std::mutex> workerLock( RecvDataMutex );

    while ( true )
    {
        // Wait for a webRequest to happen to become available
        RecieveDataCondition.wait( workerLock );

        // Make sure that we don't need to be done now!
        if ( isDone ) return;

        // Recive data here
    }

}

/////////////////////////////////////////////////////////////////
// Accessors

const char* Scrut::HttpSocket::GetHostPort() const
{
    return HostPort;
}

const char* Scrut::HttpSocket::GetHostURL() const
{
    return HostURL;
}