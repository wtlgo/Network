#ifndef StandardLogger_hpp
#define StandardLogger_hpp

#include <Logger.hpp>

namespace wtlgo {

class StandardLogger : public ILogger {
public:
	void log(CURLcode log);
};

}

#endif /* StandardLogger_hpp */