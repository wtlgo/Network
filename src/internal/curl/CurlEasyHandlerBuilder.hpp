#ifndef __WTLGO__NETWORK__INTERNAL__CURL__CURL_EASY_HANDLER_BUILDER__
#define __WTLGO__NETWORK__INTERNAL__CURL__CURL_EASY_HANDLER_BUILDER__

#include <cstddef>
#include <cstdint>
#include <string>

#include "./Types.hpp"
#include "./CurlEasyHandler.hpp"

namespace wtlgo {
namespace network {
namespace internal {
namespace curl {
class CurlEasyHandlerBuilder {
public:
    CurlEasyHandlerBuilder();

    CurlEasyHandler build() const;

    CurlEasyHandlerBuilder& verbose(bool onoff);
    CurlEasyHandlerBuilder& header(bool onoff);
    CurlEasyHandlerBuilder& no_progress(bool onoff);
    CurlEasyHandlerBuilder& no_signal(bool onoff);
    CurlEasyHandlerBuilder& wildcard_match(bool onoff);

    using write_function_t = std::size_t (*)(char* ptr, std::size_t size,
                                             std::size_t nmemb, void* userdata);
    CurlEasyHandlerBuilder& write_function(write_function_t write_callback);
    CurlEasyHandlerBuilder& write_data(void* pointer);

    using read_function_t = std::size_t (*)(char* buffer, std::size_t size,
                                            std::size_t nitems, void* userdata);
    CurlEasyHandlerBuilder& read_function(read_function_t read_callback);
    CurlEasyHandlerBuilder& read_data(void* pointer);

    using io_ctl_function_t = curlioerr (*)(CURL* handle, curliocmd cmd,
                                            void* clientp);
    CurlEasyHandlerBuilder& io_ctl_function(io_ctl_function_t ioctl_callback);
    CurlEasyHandlerBuilder& io_ctl_data(void* pointer);

    using seek_function_t = int (*)(void* userp, curl_off_t offset, int origin);
    CurlEasyHandlerBuilder& seek_function(seek_function_t seek_callback);
    CurlEasyHandlerBuilder& seek_data(void* pointer);

    using sock_function_t = int (*)(void* clientp, curl_socket_t curlfd,
                                    curlsocktype purpose);
    CurlEasyHandlerBuilder& sock_function(sock_function_t sock_callback);
    CurlEasyHandlerBuilder& sock_data(void* pointer);

    using open_socket_function_t = curl_socket_t (*)(void* clientp,
                                                     curlsocktype purpose,
                                                     curl_sockaddr* address);
    CurlEasyHandlerBuilder& open_socket_function(
        open_socket_function_t opensocket_callback);
    CurlEasyHandlerBuilder& open_socket_data(void* pointer);

    using close_socket_function_t = curl_socket_t (*)(void* clientp,
                                                      curlsocktype purpose,
                                                      curl_sockaddr* address);
    CurlEasyHandlerBuilder& close_socket_function(
        close_socket_function_t closesocket_callback);
    CurlEasyHandlerBuilder& close_socket_data(void* pointer);

    using xfer_info_function_t = int (*)(void* clientp, curl_off_t dltotal,
                                         curl_off_t dlnow, curl_off_t ultotal,
                                         curl_off_t ulnow);
    CurlEasyHandlerBuilder& xfer_info_function(
        xfer_info_function_t progress_callback);
    CurlEasyHandlerBuilder& xfer_info_data(void* pointer);

    using header_function_t = std::size_t (*)(char* buffer, std::size_t size,
                                              std::size_t nitems,
                                              void* userdata);
    CurlEasyHandlerBuilder& header_function(header_function_t header_callback);
    CurlEasyHandlerBuilder& header_data(void* pointer);

    using debug_function_t = int (*)(CURL* handle, curl_infotype type,
                                     char* data, std::size_t size,
                                     void* userptr);
    CurlEasyHandlerBuilder& debug_function(debug_function_t debug_callback);
    CurlEasyHandlerBuilder& debug_data(void* pointer);

    using ssl_ctx_function_t = CURLcode (*)(CURL* curl, void* ssl_ctx,
                                            void* userptr);
    CurlEasyHandlerBuilder& ssl_ctx_function(
        ssl_ctx_function_t ssl_ctx_callback);
    CurlEasyHandlerBuilder& ssl_ctx_data(void* pointer);

    using interleave_function_t = std::size_t (*)(void* ptr, std::size_t size,
                                                  std::size_t nmemb,
                                                  void* userdata);
    CurlEasyHandlerBuilder& interleave_function(
        interleave_function_t interleave_callback);
    CurlEasyHandlerBuilder& interleave_data(void* pointer);

    using chunk_bgn_function_t = long (*)(const void* transfer_info, void* ptr,
                                          int remains);
    using chunk_end_function_t = long (*)(void* ptr);
    CurlEasyHandlerBuilder& chunk_bgn_function(
        chunk_bgn_function_t chunk_bgn_callback);
    CurlEasyHandlerBuilder& chunk_end_function(
        chunk_end_function_t chunk_end_callback);
    CurlEasyHandlerBuilder& chunk_data(void* pointer);

    using fnmatch_function_t = int (*)(void* ptr, const char* pattern,
                                       const char* string);
    CurlEasyHandlerBuilder& fnmatch_function(
        fnmatch_function_t fnmatch_callback);
    CurlEasyHandlerBuilder& fnmatch_data(void* pointer);

    CurlEasyHandlerBuilder& supress_connect_headers(bool onoff);

    using resolver_start_function_t = int (*)(void* resolver_state,
                                              void* reserved, void* userdata);
    CurlEasyHandlerBuilder& resolver_start_function(
        resolver_start_function_t resolver_start_cb);
    CurlEasyHandlerBuilder& resolver_start_data(void* pointer);

    using prereq_function_t = int (*)(void* clientp, char* conn_primary_ip,
                                      char* conn_local_ip,
                                      int conn_primary_port,
                                      int conn_local_port);
    CurlEasyHandlerBuilder& prereq_function(prereq_function_t prereq_callback);
    CurlEasyHandlerBuilder& prereq_data(void* pointer);

    CurlEasyHandlerBuilder& error_buffer(char* buf);
    CurlEasyHandlerBuilder& std_err(FILE* stream);
    CurlEasyHandlerBuilder& fail_on_error(bool fail);
    CurlEasyHandlerBuilder& keep_sending_on_error(bool keep_sending);

    CurlEasyHandlerBuilder& url(const std::string& url);
    CurlEasyHandlerBuilder& path_as_is(bool leaveit);
    CurlEasyHandlerBuilder& protocols(long bitmask);
    CurlEasyHandlerBuilder& protocols_str(const std::string& spec);
    CurlEasyHandlerBuilder& redir_protocols(long bitmask);
    CurlEasyHandlerBuilder& redir_protocols_str(const std::string& spec);
    CurlEasyHandlerBuilder& default_protocol(const std::string& protocol);
    CurlEasyHandlerBuilder& proxy(const std::string& proxy);
    CurlEasyHandlerBuilder& pre_proxy(const std::string& preproxy);
    CurlEasyHandlerBuilder& proxy_port(std::uint16_t port);
    CurlEasyHandlerBuilder& proxy_type(long type);
    CurlEasyHandlerBuilder& no_proxy(const std::string& noproxy);
    CurlEasyHandlerBuilder& http_proxy_tunnel(bool tunnel);
    CurlEasyHandlerBuilder& connect_to(curl_slist* connect_to);
    CurlEasyHandlerBuilder& socks5_auth(long bitmask);

    // TODO: https://curl.se/libcurl/c/curl_easy_setopt.html
private:
    const curl_unique_ptr _curl;
};
}
}
}
}

#endif
