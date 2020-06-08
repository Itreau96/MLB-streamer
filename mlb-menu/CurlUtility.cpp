#include "CurlUtility.h"

CurlUtility::CurlUtility()
{
	curl = curl_easy_init();
}

void CurlUtility::RequestData(const std::string& url, MemoryStruct& mem)
{
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&mem);

	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		throw "Error: unable to process curl request...";
	}
}

void* CurlUtility::CURL_realloc(void* ptr, size_t size)
{
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

size_t CurlUtility::WriteMemoryCallback(void* ptr, size_t size, size_t nmemb, void* data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)data;

	mem->memory = (char*)CURL_realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

CurlUtility::~CurlUtility()
{
	curl_easy_cleanup(curl);
}