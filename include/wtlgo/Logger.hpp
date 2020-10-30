#ifndef Logger_hpp
#define Logger_hpp

#include <iostream>
#include <curl/curl.h>

namespace wtlgo {

class ILogger {
public:
	virtual ILogger();
	virtual ~ILogger();
	virtual void log(CURLcode log);
};

class StandardLogger : public ILogger
{
public:
	void log(CURLcode log) { std::cerr << curl_easy_strerror(log) << std::endl; }
}

#endif /* Logger_hpp */
