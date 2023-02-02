#include <memory>
#include <string>
#include <optional>
#include <stdexcept>
#include <utility>

#include "./internal/Config/MergedConfig.hpp"
#include <wtlgo/network/Config.hpp>

#include <wtlgo/network/ClientConfig.hpp>

using namespace wtlgo::network;

struct ClientConfig::Impl {
private:
    std::optional<std::string> _url;
    Config::method_opt_t _method;
    std::optional<std::string> _base_url;
    Config::headers_opt_t _headers;

public:
    Impl() = default;
    Impl(const Config::cptr_t config)
        : _url{config->url()},
          _method{config->method()},
          _base_url{config->base_url()},
          _headers{([headers = config->headers()] {
              return headers ? headers->clone() : nullptr;
          })()} {}

    Config::url_opt_ref_t url() const { return _url; }
    void url(const Config::url_ref_t url) { _url = url; }
    void clear_url() { _url = std::nullopt; }

    Config::method_opt_t method() const { return _method; }
    void method(const Config::method_t method) { _method = method; }
    void clear_method() { _method = std::nullopt; }

    Config::url_opt_ref_t base_url() const { return _base_url; }
    void base_url(const Config::url_ref_t url) { _base_url = url; }
    void clear_base_url() { _base_url = std::nullopt; }

    Config::headers_opt_t headers() const { return _headers; }
    void headers(const headers_opt_t headers) {
        if (headers) {
            _headers = headers->clone();
        } else {
            _headers = nullptr;
        }
    }
    void clear_headers() { _headers = nullptr; }
};

ClientConfig::~ClientConfig() = default;

ClientConfig::ptr_t ClientConfig::create() {
    return std::shared_ptr<ClientConfig>{new ClientConfig};
}

ClientConfig::ptr_t ClientConfig::clone(const Config::cptr_t config) {
    return std::shared_ptr<ClientConfig>{new ClientConfig{config}};
}

Config::ptr_t ClientConfig::clone() const { return clone(shared_from_this()); }

Config::ptr_t ClientConfig::merge(const Config::cptr_t rconfig) const {
    using namespace wtlgo::network::internal::config;
    return MergedConfig::merge(shared_from_this(), rconfig);
}

Config::url_opt_ref_t ClientConfig::url() const { return impl->url(); }

Config::ptr_t ClientConfig::url(const Config::url_ref_t url) {
    impl->url(url);
    return shared_from_this();
}

Config::ptr_t ClientConfig::clear_url() {
    impl->clear_url();
    return shared_from_this();
}

Config::method_opt_t ClientConfig::method() const { return impl->method(); }

Config::ptr_t ClientConfig::method(const Config::method_t method) {
    impl->method(method);
    return shared_from_this();
}

Config::ptr_t ClientConfig::clear_method() {
    impl->clear_method();
    return shared_from_this();
}

Config::url_opt_ref_t ClientConfig::base_url() const {
    return impl->base_url();
}

Config::ptr_t ClientConfig::base_url(const Config::url_ref_t url) {
    impl->base_url(url);
    return shared_from_this();
}

Config::ptr_t ClientConfig::clear_base_url() {
    impl->clear_base_url();
    return shared_from_this();
}

Config::headers_opt_t ClientConfig::headers() const { return impl->headers(); }

Config::ptr_t ClientConfig::headers(const Config::headers_opt_t headers) {
    impl->headers(headers);
    return shared_from_this();
}

Config::ptr_t ClientConfig::clear_headers() {
    impl->clear_headers();
    return shared_from_this();
}

ClientConfig::ClientConfig() : impl{std::make_unique<Impl>()} {}

ClientConfig::ClientConfig(const Config::cptr_t config)
    : impl{std::make_unique<Impl>(config)} {}
