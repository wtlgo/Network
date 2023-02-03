#include <string>
#include <cstdint>

#include <curl/curl.h>

#include "./CurlEasyHandler.hpp"
#include "./CurlEasyHandlerBuilder.hpp"

using namespace wtlgo::network::internal::curl;

CurlEasyHandlerBuilder::CurlEasyHandlerBuilder()
    : _curl{curl_easy_init(), curl_easy_cleanup} {}

CurlEasyHandler CurlEasyHandlerBuilder::build() const { return {_curl}; }

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::verbose(const bool onoff) {
    curl_easy_setopt(_curl.get(), CURLOPT_VERBOSE, static_cast<long>(onoff));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::header(const bool onoff) {
    curl_easy_setopt(_curl.get(), CURLOPT_HEADER, static_cast<long>(onoff));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::no_progress(const bool onoff) {
    curl_easy_setopt(_curl.get(), CURLOPT_NOPROGRESS, static_cast<long>(onoff));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::no_signal(const bool onoff) {
    curl_easy_setopt(_curl.get(), CURLOPT_NOSIGNAL, static_cast<long>(onoff));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::wildcard_match(
    const bool onoff) {
    curl_easy_setopt(_curl.get(), CURLOPT_WILDCARDMATCH,
                     static_cast<long>(onoff));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::write_function(
    const write_function_t write_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_WRITEFUNCTION, write_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::write_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_WRITEDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::read_function(
    const read_function_t read_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_READFUNCTION, read_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::read_data(void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_READDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::io_ctl_function(
    const io_ctl_function_t ioctl_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_IOCTLFUNCTION, ioctl_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::io_ctl_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_IOCTLDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::seek_function(
    const seek_function_t seek_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_SEEKFUNCTION, seek_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::seek_data(void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_SEEKDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::sock_function(
    const sock_function_t sock_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_SOCKOPTFUNCTION, sock_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::sock_data(void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_SOCKOPTDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::open_socket_function(
    const open_socket_function_t opensocket_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_OPENSOCKETFUNCTION,
                     opensocket_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::open_socket_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_OPENSOCKETDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::close_socket_function(
    const close_socket_function_t closesocket_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_CLOSESOCKETFUNCTION,
                     closesocket_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::close_socket_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_CLOSESOCKETDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::xfer_info_function(
    const xfer_info_function_t progress_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_XFERINFOFUNCTION, progress_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::xfer_info_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_XFERINFODATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::header_function(
    const header_function_t header_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_HEADERFUNCTION, header_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::header_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_HEADERDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::debug_function(
    const debug_function_t debug_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_DEBUGFUNCTION, debug_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::debug_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_DEBUGDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::ssl_ctx_function(
    const ssl_ctx_function_t ssl_ctx_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_SSL_CTX_FUNCTION, ssl_ctx_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::ssl_ctx_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_SSL_CTX_DATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::interleave_function(
    const interleave_function_t interleave_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_INTERLEAVEFUNCTION,
                     interleave_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::interleave_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_INTERLEAVEDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::chunk_bgn_function(
    const chunk_bgn_function_t chunk_bgn_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_CHUNK_BGN_FUNCTION,
                     chunk_bgn_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::chunk_end_function(
    const chunk_end_function_t chunk_end_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_CHUNK_END_FUNCTION,
                     chunk_end_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::chunk_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_INTERLEAVEDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::fnmatch_function(
    const fnmatch_function_t fnmatch_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_FNMATCH_FUNCTION, fnmatch_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::fnmatch_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_FNMATCH_DATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::supress_connect_headers(
    const bool onoff) {
    curl_easy_setopt(_curl.get(), CURLOPT_SUPPRESS_CONNECT_HEADERS,
                     static_cast<long>(onoff));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::resolver_start_function(
    const resolver_start_function_t resolver_start_cb) {
    curl_easy_setopt(_curl.get(), CURLOPT_RESOLVER_START_FUNCTION,
                     resolver_start_cb);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::resolver_start_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_RESOLVER_START_DATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::prereq_function(
    const prereq_function_t prereq_callback) {
    curl_easy_setopt(_curl.get(), CURLOPT_PREREQFUNCTION, prereq_callback);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::prereq_data(
    void* const pointer) {
    curl_easy_setopt(_curl.get(), CURLOPT_PREREQDATA, pointer);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::error_buffer(char* const buf) {
    curl_easy_setopt(_curl.get(), CURLOPT_ERRORBUFFER, buf);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::std_err(FILE* const stream) {
    curl_easy_setopt(_curl.get(), CURLOPT_STDERR, stream);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::fail_on_error(const bool fail) {
    curl_easy_setopt(_curl.get(), CURLOPT_FAILONERROR, static_cast<long>(fail));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::keep_sending_on_error(
    const bool keep_sending) {
    curl_easy_setopt(_curl.get(), CURLOPT_KEEP_SENDING_ON_ERROR,
                     static_cast<long>(keep_sending));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::url(const std::string& url) {
    curl_easy_setopt(_curl.get(), CURLOPT_URL, url.c_str());
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::path_as_is(const bool leaveit) {
    curl_easy_setopt(_curl.get(), CURLOPT_PATH_AS_IS,
                     static_cast<long>(leaveit));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::protocols(const long bitmask) {
    curl_easy_setopt(_curl.get(), CURLOPT_PROTOCOLS, bitmask);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::protocols_str(
    const std::string& spec) {
    curl_easy_setopt(_curl.get(), CURLOPT_PROTOCOLS_STR, spec.c_str());
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::redir_protocols(
    const long bitmask) {
    curl_easy_setopt(_curl.get(), CURLOPT_REDIR_PROTOCOLS, bitmask);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::redir_protocols_str(
    const std::string& spec) {
    curl_easy_setopt(_curl.get(), CURLOPT_PROTOCOLS_STR, spec.c_str());
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::default_protocol(
    const std::string& protocol) {
    curl_easy_setopt(_curl.get(), CURLOPT_DEFAULT_PROTOCOL, protocol.c_str());
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::proxy(
    const std::string& proxy) {
    curl_easy_setopt(_curl.get(), CURLOPT_PROXY, proxy.c_str());
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::pre_proxy(
    const std::string& preproxy) {
    curl_easy_setopt(_curl.get(), CURLOPT_PRE_PROXY, preproxy.c_str());
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::proxy_port(
    const std::uint16_t port) {
    curl_easy_setopt(_curl.get(), CURLOPT_PROXYPORT, static_cast<long>(port));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::proxy_type(const long type) {
    curl_easy_setopt(_curl.get(), CURLOPT_PROXYPORT, type);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::no_proxy(
    const std::string& noproxy) {
    curl_easy_setopt(_curl.get(), CURLOPT_NOPROXY, noproxy.c_str());
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::http_proxy_tunnel(
    const bool tunnel) {
    curl_easy_setopt(_curl.get(), CURLOPT_HTTPPROXYTUNNEL,
                     static_cast<long>(tunnel));
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::connect_to(
    curl_slist* const connect_to) {
    curl_easy_setopt(_curl.get(), CURLOPT_CONNECT_TO, connect_to);
    return *this;
}

CurlEasyHandlerBuilder& CurlEasyHandlerBuilder::socks5_auth(
    const long bitmask) {
    curl_easy_setopt(_curl.get(), CURLOPT_SOCKS5_AUTH, bitmask);
    return *this;
}
