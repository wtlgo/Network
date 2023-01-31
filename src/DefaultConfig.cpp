#include <memory>
#include <string>
#include <optional>
#include <stdexcept>
#include <utility>

#include "./internal/MergedConfig.hpp"
#include <wtlgo/network/Config.hpp>

#include <wtlgo/network/DefaultConfig.hpp>

using namespace wtlgo::network;

struct DefaultConfig::Impl {
private:
    std::optional<std::string> _url;
    Config::method_opt_t _method;
    std::optional<std::string> _base_url;

public:
    Impl() = default;
    Impl(const Impl&) = default;
    Impl(const Config::cptr_t config)
        : _url{config->url()},
          _method{config->method()},
          _base_url{config->base_url()} {}

    Config::url_opt_ref_t url() const { return _url; }
    void url(const Config::url_ref_t url) { _url = url; }
    void clear_url() { _url = std::nullopt; }

    Config::method_opt_t method() const { return _method; }
    void method(const Config::method_t method) { _method = method; }
    void clear_method() { _method = std::nullopt; }

    Config::url_opt_ref_t base_url() const { return _base_url; }
    void base_url(const Config::url_ref_t url) { _base_url = url; }
    void clear_base_url() { _base_url = std::nullopt; }
};

DefaultConfig::~DefaultConfig() = default;

DefaultConfig::ptr_t DefaultConfig::create() {
    return std::shared_ptr<DefaultConfig>{new DefaultConfig{}};
}

DefaultConfig::ptr_t DefaultConfig::clone(const Config::cptr_t config) {
    return std::shared_ptr<DefaultConfig>{new DefaultConfig{config}};
}

Config::ptr_t DefaultConfig::clone() const { return clone(shared_from_this()); }

Config::ptr_t DefaultConfig::merge(const Config::cptr_t rconfig) const {
    return internal::MergedConfig::merge(shared_from_this(), rconfig);
}

Config::url_opt_ref_t DefaultConfig::url() const { return impl->url(); }

Config::ptr_t DefaultConfig::url(const Config::url_ref_t url) {
    impl->url(url);
    return shared_from_this();
}

Config::ptr_t DefaultConfig::clear_url() {
    impl->clear_url();
    return shared_from_this();
}

Config::method_opt_t DefaultConfig::method() const { return impl->method(); }

Config::ptr_t DefaultConfig::method(const Config::method_t method) {
    impl->method(method);
    return shared_from_this();
}

Config::ptr_t DefaultConfig::clear_method() {
    impl->clear_method();
    return shared_from_this();
}

Config::url_opt_ref_t DefaultConfig::base_url() const {
    return impl->base_url();
}

Config::ptr_t DefaultConfig::base_url(const Config::url_ref_t url) {
    impl->base_url(url);
    return shared_from_this();
}

Config::ptr_t DefaultConfig::clear_base_url() {
    impl->clear_base_url();
    return shared_from_this();
}

DefaultConfig::DefaultConfig() : impl{std::make_unique<Impl>()} {}

DefaultConfig::DefaultConfig(const Config::cptr_t config)
    : impl{std::make_unique<Impl>(config)} {}
