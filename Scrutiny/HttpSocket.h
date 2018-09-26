#pragma once

#include <string>		// Use strings until we have a minimum viable product

#if defined(_WIN32) || defined(_WIN64)

	#include <assert.h>		// assert macro
	#include <WinSock2.h>	// WinSock
	#include <Ws2tcpip.h>

	#pragma comment(lib,"ws2_32.lib") //Winsock Library

#elif defined(__linux__)

	// TODO: Do other includes here or the normal socket library
	#include <sys/types.h>          /* See NOTES */
	#include <sys/socket.h>

#endif

#define MAX_HOST_LENGTH 256
#define MAX_REQUEST_LEN 1024

namespace Scrut
{
	/**
	* @brief	 WebRequest class for interfacing with the ELK stack
	*			 via sockets.
	*
	* @author	Ben Hoffman
	*/
	class HttpSocket
	{
	public:

		/** Creates a web request */
		HttpSocket(const char* aHostURL, const char* aHostPort);

		/** Destructs web request */
		~HttpSocket();

		/** 
		* Connect the socket to the Elasticsearch instance
		* 
		* @return	The result of creating the socket
		**/
		int ConnectSocket();

		/**
		* @brief Send a web request to the elastic instance using HTTP
		* 
		* @param aMethod	The HTTP method of this request (POST, PUT, GET, etc)
		* @param aIndexParam		the ELK index you are interest in
		* @param aMesg		The message you would like to send to the ELK instance
		* @return			Result from the socket attempt
		**/
		int SendRequest(const char*  aMethod, const char*  aIndexParam, const char* aMsg);


	private:

		/** The active socket that will communicate with ELK  */
		SOCKET Socket = INVALID_SOCKET;

		/* Close socket and cleanup WSA if necessary */
		void Disconnect();

		/** The host that this socket will connect to  */
		char HostURL[MAX_HOST_LENGTH];
		
		/** The host port */
		char HostPort[8];

		/** Character array for the closing connection */
		const char * ConnectionClose = "Connection: close\r\n\r\n";

		/** The request header for */
		char RequestHeader[2048];

	};
}
