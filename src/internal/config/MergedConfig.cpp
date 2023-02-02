#include <memory>

#include "./MergedConfig.hpp"
#include "./CopyOnWriteConfig.hpp"

#include <wtlgo/network/ClientConfig.hpp>

using namespace wtlgo::network;
using namespace wtlgo::network::internal::config;

MergedConfig::~MergedConfig() = default;

MergedConfig::ptr_t MergedConfig::merge(const Config::cptr_t lconfig,
                                        const Config::cptr_t rconfig) {
    return std::shared_ptr<MergedConfig>{new MergedConfig{lconfig, rconfig}};
}

Config::ptr_t MergedConfig::clone() const {
    return ClientConfig::clone(shared_from_this());
}

Config::ptr_t MergedConfig::merge(const Config::cptr_t rconfig) const {
    return merge(shared_from_this(), rconfig);
}

Config::url_opt_ref_t MergedConfig::url() const {
    return rhs->url() ? rhs->url() : lhs->url();
}

Config::ptr_t MergedConfig::url(const Config::url_ref_t url) {
    lhs->clear_url();
    rhs->url(url);

    return shared_from_this();
}

Config::ptr_t MergedConfig::clear_url() {
    lhs->clear_url();
    rhs->clear_url();

    return shared_from_this();
}

Config::method_opt_t MergedConfig::method() const {
    return rhs->method() ? rhs->method() : lhs->method();
}

Config::ptr_t MergedConfig::method(const Config::method_t method) {
    lhs->clear_method();
    rhs->method(method);

    return shared_from_this();
}

Config::ptr_t MergedConfig::clear_method() {
    lhs->clear_method();
    rhs->clear_method();

    return shared_from_this();
}

Config::url_opt_ref_t MergedConfig::base_url() const {
    return rhs->base_url() ? rhs->base_url() : lhs->base_url();
}

Config::ptr_t MergedConfig::base_url(const Config::url_ref_t url) {
    lhs->clear_base_url();
    rhs->base_url(url);

    return shared_from_this();
}

Config::ptr_t MergedConfig::clear_base_url() {
    lhs->clear_base_url();
    rhs->clear_base_url();

    return shared_from_this();
}

Config::headers_opt_t MergedConfig::headers() const {
    return rhs->headers() ? rhs->headers() : lhs->headers();
}

Config::ptr_t MergedConfig::headers(const Config::headers_opt_t headers) {
    lhs->clear_headers();
    rhs->headers(headers);

    return shared_from_this();
}

Config::ptr_t MergedConfig::clear_headers() {
    lhs->clear_headers();
    rhs->clear_headers();

    return shared_from_this();
}

MergedConfig::MergedConfig(const Config::cptr_t lconfig,
                           const Config::cptr_t rconfig)
    : lhs{CopyOnWriteConfig::adapt(lconfig)},
      rhs{CopyOnWriteConfig::adapt(rconfig)} {}
