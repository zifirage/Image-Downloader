#include <iostream>

#include <fstream>


// vcpkg
#include <curl/curl.h>


// callback(     ptr byte,   size one elem ,   number,     ptr ofstream)
size_t WriteData(void* ptr, size_t size, size_t nmemB, void* stream)
{
	std::ofstream* file = static_cast<std::ofstream*>(stream);
	if (!file->is_open())
	{
		std::cout << "error open" << std::endl;
		return 1;
	}
	size_t totalSize = size * nmemB;
	file->write(static_cast<char*>(ptr), totalSize);
	return totalSize;
}

int main()
{
	CURL* curl;
	CURLcode res;

	const char* url = "https://avatars.githubusercontent.com/u/218387576?v=4";

	// or use const char for path
	std::ofstream file("photo.jpg", std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Error create and open file.jpg" << std::endl;
		return 1;
	}

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);                   // URL;           
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);   // Func Write;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);           // stream;
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);         // location;

		res = curl_easy_perform(curl);                              // request;

		if (res != CURLE_OK)
			std::cout << "error curl: " << "\n";
		else
			std::cout << "Good save" << std::endl;


		curl_easy_cleanup(curl); // free
	}


	return 0;
}