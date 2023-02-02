#include <memory>

#include <wtlgo/network/ClientConfig.hpp>
#include <wtlgo/network/CurlClient.hpp>

using namespace wtlgo::network;

struct CurlClient::Impl {
private:
    config_ptr_t _config = ClientConfig::create();

public:
    config_ptr_t config() const { return _config; }
    void config(const config_ptr_t config) { _config = config->clone(); }
};

CurlClient::~CurlClient() = default;

CurlClient::ptr_t CurlClient::create() {
    return std::shared_ptr<CurlClient>{new CurlClient};
}

Client::config_ptr_t CurlClient::config() const { return impl->config(); }

Client::ptr_t CurlClient::config(const Client::config_ptr_t config) {
    impl->config();
    return shared_from_this();
}

CurlClient::CurlClient() : impl{std::make_unique<Impl>()} {}
