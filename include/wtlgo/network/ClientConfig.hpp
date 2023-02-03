#ifndef __WTLGO__NETWORK__CLIENT_CONFIG__
#define __WTLGO__NETWORK__CLIENT_CONFIG__

#include <memory>

#include <wtlgo/network/Config.hpp>

namespace wtlgo {
namespace network {
class ClientConfig : public Config,
                     public std::enable_shared_from_this<ClientConfig> {
public:
    using ptr_t = std::shared_ptr<ClientConfig>;
    using cptr_t = std::shared_ptr<const ClientConfig>;

    virtual ~ClientConfig();

    [[nodiscard]] static ClientConfig::ptr_t create();
    [[nodiscard]] static ClientConfig::ptr_t clone(Config::cptr_t);

    Config::ptr_t clone() const override;
    Config::ptr_t merge(Config::cptr_t) const override;

    Config::url_opt_ref_t url() const override;
    Config::ptr_t url(Config::url_ref_t) override;
    Config::ptr_t clear_url() override;

    Config::method_opt_t method() const override;
    Config::ptr_t method(Config::method_t) override;
    Config::ptr_t clear_method() override;

    Config::url_opt_ref_t base_url() const override;
    Config::ptr_t base_url(Config::url_ref_t) override;
    Config::ptr_t clear_base_url() override;

    Config::headers_opt_t headers() const override;
    Config::ptr_t headers(headers_opt_t) override;
    Config::ptr_t clear_headers() override;

protected:
    ClientConfig();
    ClientConfig(const Config::cptr_t);

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;
};
}
}

#endif
