#include <memory>

#include <wtlgo/network/Config.hpp>
#include <wtlgo/network/DefaultConfig.hpp>

using namespace wtlgo::network;

struct DefaultConfig::Impl {};

DefaultConfig::~DefaultConfig() = default;

DefaultConfig::ptr_t DefaultConfig::create() {
    return std::shared_ptr<DefaultConfig>{new DefaultConfig{}};
}

Config::ptr_t DefaultConfig::clone() const {
    return std::shared_ptr<DefaultConfig>{new DefaultConfig{impl}};
}

DefaultConfig::DefaultConfig() : impl{std::make_unique<Impl>()} {}

DefaultConfig::DefaultConfig(const std::unique_ptr<Impl>& impl)
    : impl{std::make_unique<Impl>(*impl)} {}
