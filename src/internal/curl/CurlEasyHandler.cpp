#include <curl/curl.h>

#include "./CurlEasyHandler.hpp"

using namespace wtlgo::network::internal::curl;

CurlEasyHandler::CurlEasyHandler()
    : _curl{curl_easy_init(), curl_easy_cleanup} {}

CurlEasyHandler::CurlEasyHandler(const curl_unique_ptr& curl)
    : _curl{curl_easy_duphandle(curl.get()), curl_easy_cleanup} {}

CurlEasyHandler::CurlEasyHandler(const CurlEasyHandler& handler)
    : CurlEasyHandler(handler._curl) {}

CURLcode CurlEasyHandler::perform() const {
    return curl_easy_perform(_curl.get());
}
