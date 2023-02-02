#ifndef __WTLGO__NETWORK__INTERNAL__CURL__TYPES__
#define __WTLGO__NETWORK__INTERNAL__CURL__TYPES__

#include <memory>

#include <curl/curl.h>

namespace wtlgo {
namespace network {
namespace internal {
namespace curl {
using curl_shared_ptr = std::shared_ptr<CURL>;
using curl_unique_ptr = std::unique_ptr<CURL, void (*)(CURL*)>;
}
}
}
}

#endif
