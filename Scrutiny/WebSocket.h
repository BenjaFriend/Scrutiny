/**
* @brief	 WebRequest class for interfacing with the ELK stack
*			 via sockets.
* 
* @author	Ben Hoffman
*/

#pragma once

#include <string>	// Use strings until we have a minimum viable product
#include <winsock.h> // TODO: Make this portable

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
		*/
		void SendRequest(const char* aURL, const char* aMsg);

	};
}