#pragma once

#include <stdio.h>
#include "HttpSocket.h"

namespace Scrut
{
	/**
	* @brief	Provide functionality for the user make simple calls to elasticsearch.
	*			Have the main configuration for the indexing patterns of ELK, what data types
	*			to send, etc.
	*
	* @author	Ben Hoffman
	*/
	class Scrutiny
	{

	public:

		/** Default Constructor */
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
		* Get information about an index in elasticsearch
		* 
		* @param index		The index you would like to recieve information about
		*/
		int GetIndex(const char* aIndex);

	private:

		/** The socket we will use to communicate with the ELK stack */
		HttpSocket * ELK_Socket = nullptr;

		/** The index that the user would like to report to */
		char* CurrentIndex = nullptr;

	};
}