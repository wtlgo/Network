#ifndef __WTLGO__NETWORK__CLIENT_HPP__
#define __WTLGO__NETWORK__CLIENT_HPP__

#include <memory>

#include <wtlgo/network/Config.hpp>

namespace wtlgo {
namespace network {
class Client {
public:
    Client();
    Client(const Config& config);
    virtual ~Client();

    Config& config();
    const Config& config() const;

private:
    struct ClientImpl;
    std::unique_ptr<ClientImpl> impl;
};
}
}

#endif
