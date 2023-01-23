#ifndef __WTLGO__NETWORK__CONFIG__
#define __WTLGO__NETWORK__CONFIG__

#include <memory>

namespace wtlgo {
namespace network {
struct Config {
    using ptr_t = std::shared_ptr<Config>;
    using cptr_t = std::shared_ptr<const Config>;

    virtual ~Config() = default;
    virtual ptr_t clone() const = 0;
};
}
}

#endif
