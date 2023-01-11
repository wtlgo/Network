#include <memory>

#include <wtlgo/network/Client.hpp>
#include <wtlgo/network/Config.hpp>

using namespace wtlgo::network;

struct Client::ClientImpl {
    Config _config;

    ClientImpl() = default;
    ClientImpl(const Config& config) : _config{config} {}

    Config& config() { return _config; }
    const Config& config() const { return _config; }
};

Client::Client() : impl{std::make_unique<ClientImpl>()} {}
Client::Client(const Config& config)
    : impl{std::make_unique<ClientImpl>(config)} {}
Client::~Client() = default;

Config& Client::config() { return impl->config(); }
const Config& Client::config() const { return impl->config(); }
