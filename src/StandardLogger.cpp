#include <iostream>

#include <StandardLogger.hpp>

using namespace wtlgo;

void StandardLogger::log(CURLcode log) {
	std::cerr << curl_easy_strerror(log) << std::endl;
}