#ifndef __WTLGO__NETWORK__INTERNAL__CURL__CURL_EASY_HANDLER__
#define __WTLGO__NETWORK__INTERNAL__CURL__CURL_EASY_HANDLER__

#include <memory>
#include <ostream>

#include "./Types.hpp"

namespace wtlgo {
namespace network {
namespace internal {
namespace curl {
class CurlEasyHandler {
public:
    CurlEasyHandler();
    CurlEasyHandler(const curl_unique_ptr&);
    CurlEasyHandler(const CurlEasyHandler&);

    CURLcode perform() const;

private:
    const curl_unique_ptr _curl;
};
}
}
}
}

#endif
