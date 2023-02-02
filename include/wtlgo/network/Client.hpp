#ifndef __WTLGO__NETWORK__CLIENT__
#define __WTLGO__NETWORK__CLIENT__

#include <memory>

#include <wtlgo/network/Config.hpp>

namespace wtlgo {
namespace network {
struct Client {
    using ptr_t = std::shared_ptr<Client>;
    using cptr_t = std::shared_ptr<const Client>;

    virtual ~Client() = default;

    using config_ptr_t = Config::cptr_t;

    virtual config_ptr_t config() const = 0;
    virtual ptr_t config(config_ptr_t) = 0;
};
}
}

#endif
