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
    [[nodiscard]] static DefaultConfig::ptr_t clone(Config::cptr_t);

    Config::ptr_t clone() const override;
    Config::ptr_t merge(Config::cptr_t) const override;

    Config::url_opt_ref_t url() const override;
    Config::ptr_t url(Config::url_ref_t) override;
    Config::ptr_t clear_url() override;

    Config::method_opt_t method() const override;
    Config::ptr_t method(Config::method_t) override;
    Config::ptr_t clear_method() override;

protected:
    DefaultConfig();
    DefaultConfig(const Config::cptr_t);

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;
};

using DConfig = DefaultConfig;
}
}

#endif
