#include <memory>

#include <wtlgo/network/ClientConfig.hpp>
#include "./MergedConfig.hpp"

#include "./CopyOnWriteConfig.hpp"

using namespace wtlgo::network;
using namespace wtlgo::network::internal;

struct CopyOnWriteConfig::Impl {
private:
    Config::cptr_t solid;
    Config::ptr_t liquid;

    void liquify() {
        if (!solid) return;

        liquid = ClientConfig::clone(solid);
        solid = nullptr;
    }

    Config::cptr_t cptr() const { return solid ? solid : liquid; }
    Config::ptr_t ptr() {
        liquify();
        return liquid;
    }

public:
    Impl(const Config::cptr_t config) : solid{config}, liquid{nullptr} {}

    Config::url_opt_ref_t url() const { return cptr()->url(); }
    void url(const Config::url_ref_t url) { ptr()->url(url); }
    void clear_url() { ptr()->clear_url(); }

    Config::method_opt_t method() const { return cptr()->method(); }
    void method(const Config::method_t method) { ptr()->method(method); }
    void clear_method() { ptr()->clear_method(); }

    Config::url_opt_ref_t base_url() const { return cptr()->base_url(); }
    void base_url(const Config::url_ref_t url) { ptr()->base_url(url); }
    void clear_base_url() { ptr()->clear_base_url(); }

    Config::headers_opt_t headers() const { return cptr()->headers(); }
    void headers(const headers_opt_t headers) { ptr()->headers(headers); }
    void clear_headers() { ptr()->clear_headers(); }
};

CopyOnWriteConfig::~CopyOnWriteConfig() = default;

CopyOnWriteConfig::ptr_t CopyOnWriteConfig::adapt(const Config::cptr_t config) {
    return std::shared_ptr<CopyOnWriteConfig>{new CopyOnWriteConfig{config}};
}

Config::ptr_t CopyOnWriteConfig::clone() const {
    return ClientConfig::clone(shared_from_this());
}

Config::ptr_t CopyOnWriteConfig::merge(const Config::cptr_t rconfig) const {
    return MergedConfig::merge(shared_from_this(), rconfig);
}

Config::url_opt_ref_t CopyOnWriteConfig::url() const { return impl->url(); }
Config::ptr_t CopyOnWriteConfig::url(const Config::url_ref_t url) {
    impl->url(url);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_url() {
    impl->clear_url();
    return shared_from_this();
}

Config::method_opt_t CopyOnWriteConfig::method() const {
    return impl->method();
}

Config::ptr_t CopyOnWriteConfig::method(const Config::method_t method) {
    impl->method(method);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_method() {
    impl->clear_method();
    return shared_from_this();
}

Config::url_opt_ref_t CopyOnWriteConfig::base_url() const {
    return impl->base_url();
}

Config::ptr_t CopyOnWriteConfig::base_url(const Config::url_ref_t url) {
    impl->base_url(url);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_base_url() {
    impl->clear_base_url();
    return shared_from_this();
}

Config::headers_opt_t CopyOnWriteConfig::headers() const {
    return impl->headers();
}

Config::ptr_t CopyOnWriteConfig::headers(const Config::headers_opt_t headers) {
    impl->headers(headers);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_headers() {
    impl->clear_headers();
    return shared_from_this();
}

CopyOnWriteConfig::CopyOnWriteConfig(const Config::cptr_t config)
    : impl{std::make_unique<Impl>(config)} {}
