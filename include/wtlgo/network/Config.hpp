#ifndef __WTLGO__NETWORK__CONFIG__
#define __WTLGO__NETWORK__CONFIG__

#include <memory>
#include <string_view>
#include <optional>

#include <wtlgo/network/HttpMethod.hpp>

namespace wtlgo {
namespace network {
struct Config {
    using ptr_t = std::shared_ptr<Config>;
    using cptr_t = std::shared_ptr<const Config>;

    virtual ~Config() = default;

    [[nodiscard]] virtual ptr_t clone() const = 0;
    [[nodiscard]] virtual ptr_t merge(cptr_t) const = 0;

    using url_ref_t = std::string_view;
    using url_opt_ref_t = std::optional<url_ref_t>;

    virtual url_opt_ref_t url() const = 0;
    virtual ptr_t url(url_ref_t) = 0;
    virtual ptr_t clear_url() = 0;

    using method_t = HttpMethod;
    using method_opt_t = std::optional<method_t>;

    virtual method_opt_t method() const = 0;
    virtual ptr_t method(method_t) = 0;
    virtual ptr_t clear_method() = 0;
};
}
}

#endif
