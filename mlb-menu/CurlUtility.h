#pragma once

#include <string>
#include "curl/curl.h"

/**
* Struct used to encapsulate data returned by curl request.
*/
struct MemoryStruct {
	char* memory;
	size_t size;
};

/**
* Class used to provide web request utility functionality based on the curl library
*/
class CurlUtility
{
public:
	/*
	* Default constructor
	*/
	CurlUtility();
	/*
	* Default destructor
	*/
	~CurlUtility();
	/**
	* Helper function to return data given a valid url request.
	* @param url Url string request for data
	* @param mem Memory struct providing storage for request data
	* Note: Adapted from nifty libcurl getinmemory example
	*/
	void RequestData(const std::string& url, MemoryStruct& mem);
private:
	/**
	* Callback function for writing data from curl request.
	* Note: Adapted from nifty libcurl getinmemory example
	*/
	static size_t WriteMemoryCallback(void* ptr, size_t size, size_t nmemb, void* data);
	/**
	* Helper function for buffering curl data.
	* Note: Adapted from nifty libcurl getinmemory example
	*/
	static void* CURL_realloc(void* ptr, size_t size);
	/*
	* Curl object
	*/
	CURL* curl;
};
