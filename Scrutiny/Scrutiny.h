#pragma once

#include <stdio.h>
#include "HttpSocket.h"

namespace Scrut
{
#define  GET "GET"
#define  POST "POST"
#define  PUT "PUT"
#define  XDELETE "XDELETE"


	/**
	* @brief	Provide functionality for the user make simple calls to Elasticsearch.
	*			Have the main configuration for the indexing patterns of ELK, what data types
	*			to send, etc.
	*
	* @author	Ben Hoffman
	*/
	class Scrutiny
	{

	public:



		/** 
		* Constructor for a specific server and port 
		* 
		* @param aServerAddress		The address of the ELK server to connect with
		* @param aServerPort		The port of the ELK serve to connect with
		*/
		Scrutiny(const char* aServerAddress, const char* aServerPort);

		/** Default destructor */
		~Scrutiny();

		/**
		* Send a test web socket request to the ELK stack
		*
		* @return	Status of the request
		*/
		int TestRequest();

		/**
		* Get information about an index in Elasticsearch
		* 
		* @param index		The index you would like to receive information about
		*/
		int GetIndex(const char* aIndex);

		/**
		* @param aIndex		The Elasticsearch index to delete
		* 
		* @return	Status of the request to the server
		*/
		int DeleteIndex(const char* aIndex);

	private:

		/** private Default Constructor */
		Scrutiny();

		/** The socket we will use to communicate with the ELK stack */
		HttpSocket * ELK_Socket = nullptr;

		/** The index that the user would like to report to */
		char* CurrentIndex = nullptr;

	};
}