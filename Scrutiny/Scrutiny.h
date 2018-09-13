#pragma once

/**
* @brief	Provide functionality for the user make simple calls to elasticsearch.
*			Have the main configuration for the indexing patterns of ELK, what data types
*			to send, etc.
*
* @author	Ben Hoffman
*/

#include <stdio.h>
#include "WebSocket.h"

namespace Scrut
{
	class Scrutiny
	{

	public:

		/** Default Constructor*/
		Scrutiny();

		/** Default destructor */
		~Scrutiny();

		/**
		* Send a test web socket request to the ELK stack
		*
		* @return	Status of the request
		*/
		int TestRequest();

		/**
		* @brief Test a functoin for ensuring our DLL can be used properly
		*
		* @param a	First number to be multiplied
		* @param b	Second number to be multiplied
		*/
		float TestMultiply(float a, float b);

	};
}