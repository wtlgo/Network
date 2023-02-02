#ifndef __WTLGO__NETWORK__CURL_CLIENT__
#define __WTLGO__NETWORK__CURL_CLIENT__

#include <memory>

#include <wtlgo/network/Client.hpp>

namespace wtlgo {
namespace network {
class CurlClient : public Client,
                   public std::enable_shared_from_this<CurlClient> {
public:
    using ptr_t = std::shared_ptr<CurlClient>;
    using cptr_t = std::shared_ptr<const CurlClient>;

    virtual ~CurlClient();

    [[nodiscard]] static CurlClient::ptr_t create();

    Client::config_ptr_t config() const override;
    Client::ptr_t config(Client::config_ptr_t) override;

protected:
    CurlClient();

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;
};
}
}

#endif
