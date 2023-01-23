#ifndef __WTLGO__NETWORK__DEFAULT_CONFIG__
#define __WTLGO__NETWORK__DEFAULT_CONFIG__

#include <memory>

#include <wtlgo/network/Config.hpp>

namespace wtlgo {
namespace network {
class DefaultConfig : public Config,
                      public std::enable_shared_from_this<DefaultConfig> {
public:
    using ptr_t = std::shared_ptr<DefaultConfig>;
    using cptr_t = std::shared_ptr<const DefaultConfig>;

    virtual ~DefaultConfig();

    [[nodiscard]] static DefaultConfig::ptr_t create();

    Config::ptr_t clone() const override;

protected:
    DefaultConfig();

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;

    DefaultConfig(const std::unique_ptr<Impl>&);
};
}
}

#endif
