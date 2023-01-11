#include <atomic>
#include <memory>

#include <curl/curl.h>

#include <wtlgo/network/CurlController.hpp>

using namespace wtlgo::network;

struct CurlController::CurlControllerImpl {
    std::atomic_bool did_init{false};
    void global_init() {
        if (did_init.exchange(true)) return;
        curl_global_init(CURL_GLOBAL_ALL);
    }

    curl_handler_t get_handler(CurlController& controller) {
        controller.global_init();
        return {curl_easy_init(), curl_easy_cleanup};
    }
};

CurlController& CurlController::instance() {
    static CurlController instance;
    return instance;
}

void CurlController::global_init() { impl->global_init(); }

CurlController::curl_handler_t CurlController::get_handler() {
    return impl->get_handler(*this);
}

CurlController::CurlController()
    : impl{std::make_unique<CurlControllerImpl>()} {}
CurlController::~CurlController() = default;
