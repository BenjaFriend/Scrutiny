#pragma once

#include "stdafx.h"

#include "HttpSocket.h"
#include <ctime>



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
        /// Start a report and configure the basic headers for the request.
        /// Adds the current time to the request
        /// </summary>
        void StartReport();

        /// <summary>
        /// Add the closing tag to the report and send it to ELK with
        /// a POST request. 
        /// </summary>
        const int SendReport();

        /// <summary>
        /// Adds this float to the message being sent to Elasticsearch
        /// </summary>
        /// <param name="aKey">The name of this float value</param>
        /// <param name="aValue">The float value to report</param>
        /// <returns>The status of the request</returns>
        void ReportFloat( const char* aKey, float aValue );

        /// <summary>
        /// Append a report of a character with the given key values pair to
        /// the current request
        /// </summary>
        /// <param name="aKey">The name of the key in Elasticsearch</param>
        /// <param name="aVal">character value</param>
        void ReportCharacter( const char* aKey, const char* aVal );

        /// <summary>
        /// Report a generic type given a way to put this type into a char* 
        /// </summary>
        /// <param name="aKey">The name of the key in Elasticsearch</param>
        /// <param name="aVal">The value to report</param>
        /// <param name="toString_func">A fucntion that will specify how to put this
        /// type into a char*</param>
        template <class T>
        void ReportGeneric(
            const char* aKey,
            T* aVal,
            void( *toString_func )( char* aBuffer, size_t buf_size, T* aValue )
        );

        /// <summary>
        /// Report a generic type given a way to put this type into a char* with member
        /// functions
        /// </summary>
        /// <param name="aKey">The name of the key in Elasticsearch</param>
        /// <param name="aVal">The value to report</param>
        /// <param name="toString_func">A fucntion that will specify how to put this
        /// type into a char*</param>
        template <class T>
        void ReportGeneric(
            const char* aKey,
            T* aVal,
            void( T::*toString_func )( char* aBuffer, size_t buf_size, T* aValue )
        );

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

        /** Return the current request that is being built, or last sent. */
        const char* GetCurrentRequest() const;

	private:

		/** The socket we will use to communicate with the ELK stack */
		HttpSocket * ELK_Socket = nullptr;

		/** The index that the user would like to report to */
		char* CurrentIndex = nullptr;

        /** The current request buffer */
        char* CurrentRequest = nullptr;
	};


    ////////////////////////////////////////////////////////////////////
    // Template class implementations //////////////////////////////////

    template<class T>
    void Scrutiny::ReportGeneric( 
        const char * aKey,
        T * aVal,
        void( *toString_func )( char *aBuffer, size_t buf_size, T *aValue )
    )
    {
        assert( aKey != nullptr && aVal != nullptr && toString_func != nullptr );

        strcat_s( CurrentRequest, REQUEST_LEN, ", \"" );
        strcat_s( CurrentRequest, REQUEST_LEN, aKey );
        strcat_s( CurrentRequest, REQUEST_LEN, "\": \"" );
        char buf[ _CVTBUFSIZE ];
        strcpy_s( buf, _CVTBUFSIZE, "\0" );

        toString_func( buf, _CVTBUFSIZE, aVal );

        strcat_s( CurrentRequest, REQUEST_LEN, buf );
        strcat_s( CurrentRequest, REQUEST_LEN, "\"" );
    }

    template<class T>
    void Scrutiny::ReportGeneric( const char* aKey,
        T* aVal,
        void( T::*toString_func )( char* aBuffer, size_t buf_size, T* aValue ) 
    )
    {
        assert( aKey != nullptr && aVal != nullptr && toString_func != nullptr );

        strcat_s( CurrentRequest, REQUEST_LEN, ", \"" );
        strcat_s( CurrentRequest, REQUEST_LEN, aKey );
        strcat_s( CurrentRequest, REQUEST_LEN, "\": \"" );
        char buf[ _CVTBUFSIZE ];
        strcpy_s( buf, _CVTBUFSIZE, "\0" );

        (aVal->*toString_func)( buf, _CVTBUFSIZE, aVal );

        strcat_s( CurrentRequest, REQUEST_LEN, buf );
        strcat_s( CurrentRequest, REQUEST_LEN, "\"" );
    }
}