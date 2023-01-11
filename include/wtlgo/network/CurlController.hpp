#ifndef __WTLGO__NETWORK__CURL_CONTROLLER_HPP__
#define __WTLGO__NETWORK__CURL_CONTROLLER_HPP__

#include <memory>

#include <curl/curl.h>

namespace wtlgo {
namespace network {
class CurlController {
public:
    using curl_handler_t = std::unique_ptr<CURL, void (*)(CURL*)>;

    CurlController(const CurlController&) = delete;
    void operator=(const CurlController&) = delete;

    static CurlController& instance();

    void global_init();

    curl_handler_t get_handler();

private:
    CurlController();
    ~CurlController();

    struct CurlControllerImpl;
    std::unique_ptr<CurlControllerImpl> impl;
};
}
}

#endif
