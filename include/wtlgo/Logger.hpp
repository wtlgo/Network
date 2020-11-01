#ifndef Logger_hpp
#define Logger_hpp

#include <curl/curl.h>

namespace wtlgo {

class ILogger {
public:
	virtual void log(CURLcode log) = 0;
};

}

#endif /* Logger_hpp */
