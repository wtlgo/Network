#include <memory>

#include <wtlgo/network/DefaultConfig.hpp>
#include "./MergedConfig.hpp"

#include "./CopyOnWriteConfig.hpp"

using namespace wtlgo::network;
using namespace wtlgo::network::internal;

struct CopyOnWriteConfig::Impl {
private:
    Config::cptr_t solid;
    Config::ptr_t liquid;

    void solidify() {
        if (!solid) return;

        liquid = DefaultConfig::clone(solid);
        solid = nullptr;
    }

    Config::cptr_t cptr() const { return solid ? solid : liquid; }
    Config::ptr_t ptr() {
        solidify();
        return liquid;
    }

public:
    Impl(const Config::cptr_t config) : solid{config}, liquid{nullptr} {}

    Config::url_opt_ref_t url() const { return cptr()->url(); }
    void url(const Config::url_ref_t url) { ptr()->url(url); }
    void clear_url() { ptr()->clear_url(); }
};

CopyOnWriteConfig::~CopyOnWriteConfig() = default;

CopyOnWriteConfig::ptr_t CopyOnWriteConfig::adapt(const Config::cptr_t config) {
    return std::shared_ptr<CopyOnWriteConfig>{new CopyOnWriteConfig{config}};
}

Config::ptr_t CopyOnWriteConfig::clone() const {
    return DefaultConfig::clone(shared_from_this());
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

CopyOnWriteConfig::CopyOnWriteConfig(const Config::cptr_t config)
    : impl{std::make_unique<Impl>(config)} {}
