#include <memory>

#include "./MergedConfig.hpp"
#include "./CopyOnWriteConfig.hpp"

#include <wtlgo/network/DefaultConfig.hpp>

using namespace wtlgo::network;
using namespace wtlgo::network::internal;

struct MergedConfig::Impl {
private:
    Config::ptr_t lhs;
    Config::ptr_t rhs;

public:
    Impl(const Config::cptr_t lhs, const Config::cptr_t rhs)
        : lhs{CopyOnWriteConfig::adapt(lhs)},
          rhs{CopyOnWriteConfig::adapt(rhs)} {}

    Config::url_opt_ref_t url() const {
        return rhs->url() ? rhs->url() : lhs->url();
    }

    void url(const Config::url_ref_t url) {
        lhs->clear_url();
        rhs->url(url);
    }

    void clear_url() {
        lhs->clear_url();
        rhs->clear_url();
    }
};

MergedConfig::~MergedConfig() = default;

MergedConfig::ptr_t MergedConfig::merge(const Config::cptr_t lconfig,
                                        const Config::cptr_t rconfig) {
    return std::shared_ptr<MergedConfig>{new MergedConfig{lconfig, rconfig}};
}

Config::ptr_t MergedConfig::clone() const {
    return DefaultConfig::clone(shared_from_this());
}

Config::ptr_t MergedConfig::merge(const Config::cptr_t rconfig) const {
    return merge(shared_from_this(), rconfig);
}

Config::url_opt_ref_t MergedConfig::url() const { return impl->url(); }

Config::ptr_t MergedConfig::url(const Config::url_ref_t url) {
    impl->url(url);
    return shared_from_this();
}

Config::ptr_t MergedConfig::clear_url() {
    impl->clear_url();
    return shared_from_this();
}

MergedConfig::MergedConfig(const Config::cptr_t lconfig,
                           const Config::cptr_t rconfig)
    : impl{std::make_unique<Impl>(lconfig, rconfig)} {}
