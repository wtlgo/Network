#ifndef __WTLGO__NETWORK__INTERNAL__CONFIG__COPY_ON_WRITE_CONFIG__
#define __WTLGO__NETWORK__INTERNAL__CONFIG__COPY_ON_WRITE_CONFIG__

#include <wtlgo/network/Config.hpp>
#include <memory>

namespace wtlgo {
namespace network {
namespace internal {
namespace config {
class CopyOnWriteConfig
    : public Config,
      public std::enable_shared_from_this<CopyOnWriteConfig> {
public:
    using ptr_t = std::shared_ptr<CopyOnWriteConfig>;
    using cptr_t = std::shared_ptr<const CopyOnWriteConfig>;

    virtual ~CopyOnWriteConfig();

    [[nodiscard]] static CopyOnWriteConfig::ptr_t adapt(Config::cptr_t);

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
    CopyOnWriteConfig(Config::cptr_t);

private:
    Config::cptr_t solid;
    Config::ptr_t liquid;

    Config::cptr_t cptr() const;
    Config::ptr_t ptr();
};
}
}
}
}

#endif
