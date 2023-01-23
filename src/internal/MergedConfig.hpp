#ifndef __WTLGO__NETWORK__INTERNAL__MERGED_CONFIG__
#define __WTLGO__NETWORK__INTERNAL__MERGED_CONFIG__

#include <wtlgo/network/Config.hpp>
#include <memory>

namespace wtlgo {
namespace network {
namespace internal {
class MergedConfig : public Config,
                     public std::enable_shared_from_this<MergedConfig> {
public:
    using ptr_t = std::shared_ptr<MergedConfig>;
    using cptr_t = std::shared_ptr<const MergedConfig>;

    virtual ~MergedConfig();

    [[nodiscard]] static MergedConfig::ptr_t merge(Config::cptr_t,
                                                   Config::cptr_t);

    Config::ptr_t clone() const;
    Config::ptr_t merge(Config::cptr_t) const;

    Config::url_opt_ref_t url() const;
    Config::ptr_t url(Config::url_ref_t);
    Config::ptr_t clear_url();

protected:
    MergedConfig(Config::cptr_t, Config::cptr_t);

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;
};
}
}
}

#endif
