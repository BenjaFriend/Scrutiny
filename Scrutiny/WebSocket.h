/**
* @brief	 WebRequest class for interfacing with the ELK stack
*			 via sockets.
* 
* @author	Ben Hoffman
*/

#pragma once

#include <string>		// Use strings until we have a minimum viable product
#include <WinSock2.h>	// WinSock
#include <Ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

namespace Scrut
{
	class WebSocket
	{
	public:

		/** Creates a web request */
		WebSocket();

		/** Destructs web req */
		~WebSocket();


		/**
		* @brief Send a web reuqest to the elastic instance using HTTP
		*
		* @param aDest  The destination IP address of the ELK instance
		* @param aMesg	The message you would like to send to the ELK instance
		* @return		Result from the socket attempt
		*/
		int SendRequest(const char* aURL, const char* aMsg);

	private:

		/** The active socket that will communicate with ELK  */
		SOCKET Socket = INVALID_SOCKET;

		/** Close socket and cleanup WSA if necessary */
		void Disconnect();

	};
}