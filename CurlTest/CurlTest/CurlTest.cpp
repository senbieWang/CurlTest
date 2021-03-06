// CurlTest.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>

#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment(lib,"curl/libcurl_a_debug.lib")
#else
#pragma comment(lib,"curl/libcurl_a.lib")
#endif

static int writer(char *data, size_t size, size_t nmemb,
	std::string *writerData)
{
	if (writerData == NULL)
		return 0;

	writerData->append(data, size*nmemb);

	return size * nmemb;
}

int main()
{
	std::string content;
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = nullptr;
	curl = curl_easy_init();

	if (curl) 
	{
		curl_easy_setopt(curl,CURLOPT_URL,"https://www.baidu.com/");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	std::cout << content;

	std::cout << "\n\n Press any key to exit." << std::endl;
	std::cin.get();
	return 0;
}

