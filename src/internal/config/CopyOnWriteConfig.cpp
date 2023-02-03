#include <memory>

#include <wtlgo/network/ClientConfig.hpp>
#include "./MergedConfig.hpp"

#include "./CopyOnWriteConfig.hpp"

using namespace wtlgo::network;
using namespace wtlgo::network::internal::config;

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

Config::url_opt_ref_t CopyOnWriteConfig::url() const { return cptr()->url(); }
Config::ptr_t CopyOnWriteConfig::url(const Config::url_ref_t url) {
    ptr()->url(url);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_url() {
    ptr()->clear_url();
    return shared_from_this();
}

Config::method_opt_t CopyOnWriteConfig::method() const {
    return cptr()->method();
}

Config::ptr_t CopyOnWriteConfig::method(const Config::method_t method) {
    ptr()->method(method);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_method() {
    ptr()->clear_method();
    return shared_from_this();
}

Config::url_opt_ref_t CopyOnWriteConfig::base_url() const {
    return cptr()->base_url();
}

Config::ptr_t CopyOnWriteConfig::base_url(const Config::url_ref_t url) {
    ptr()->base_url(url);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_base_url() {
    ptr()->clear_base_url();
    return shared_from_this();
}

Config::headers_opt_t CopyOnWriteConfig::headers() const {
    return cptr()->headers();
}

Config::ptr_t CopyOnWriteConfig::headers(const Config::headers_opt_t headers) {
    ptr()->headers(headers);
    return shared_from_this();
}

Config::ptr_t CopyOnWriteConfig::clear_headers() {
    ptr()->clear_headers();
    return shared_from_this();
}

CopyOnWriteConfig::CopyOnWriteConfig(const Config::cptr_t config)
    : solid{config}, liquid{nullptr} {}

Config::cptr_t CopyOnWriteConfig::cptr() const {
    return solid ? solid : liquid;
}

Config::ptr_t CopyOnWriteConfig::ptr() {
    if (solid) {
        liquid = ClientConfig::clone(solid);
        solid = nullptr;
    }

    return liquid;
}
