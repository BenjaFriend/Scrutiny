#pragma once

#include <stdio.h>
#include "HttpSocket.h"
#include <ctime>
#include <time.h>
#include <iostream>
#include <stdlib.h>

namespace Scrut
{
#define GET "GET"
#define POST "POST"
#define PUT "PUT"
#define XDELETE "XDELETE"
#define REQUEST_LEN 1024
#define TIME_BUF_SIZE 64

	/// <summary>
	/// Provide functionality for the user make simple calls to Elasticsearch.
	/// Have the main configuration for the indexing patterns of ELK, what data types
	/// to send, etc.
	/// </summary>
	/// <author>Ben Hoffman</author>
	class Scrutiny
	{

	public:

		/// <summary>
		/// Constructor for a specific server and port 
		/// </summary>
		/// <param name="aServerAddress">The address of the ELK server to connect with</param>
		/// <param name="aServerPort">The port of the ELK serve to connect with</param>
		Scrutiny( const char* aServerAddress, const char* aServerPort );

		/// <summary>
		/// Default destructor; Clean u Sockets
		/// </summary>
		~Scrutiny();

		/// <summary>
		/// Send a test web HTTP socket to to the ELK stack
		/// </summary>
		/// <returns>Status of the web request.</returns>
        const int TestRequest();

		/// <summary>
		/// Get information about an index in Elasticsearch 
		/// </summary>
		/// <param name="aIndex">The index you would like to receive information about</param>
		/// <returns>Status of the web request</returns>
		const int GetIndex( const char* aIndex ) const;

		/// <summary>
		/// The Elasticsearch index to delete
		/// </summary>
		/// <param name="aIndex">Status of the request to the server</param>
		/// <returns>Status of the web request</returns>
		const int DeleteIndex( const char* aIndex ) const;

        /// <summary>
        /// Get the current time format that is proper for Elasticsearch
        /// </summary>
        /// <returns>timestamp formatted in a way to be reported for ELK</returns>
        const char* AppendCurrentTimeFormat( char* aOutArray );

        /////////////////////////////////////////////////////////////////
        // Accessors

        /** Return the current ELK index that is being reported to */
        const char* GetCurrentIndex() const;

	private:

		/** The socket we will use to communicate with the ELK stack */
		HttpSocket * ELK_Socket = nullptr;

		/** The index that the user would like to report to */
		char* CurrentIndex = nullptr;

        /** The current request buffer */
        char* CurrentRequest = nullptr;
	};
}