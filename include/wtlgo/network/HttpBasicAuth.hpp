#ifndef __WTLGO__NETWORK__HTTP_BASIC_AUTH__
#define __WTLGO__NETWORK__HTTP_BASIC_AUTH__

#include <memory>
#include <string_view>

namespace wtlgo {
namespace network {
struct HttpBasicAuth {
    using sptr_t = std::shared_ptr<HttpBasicAuth>;
    using csptr_t = std::shared_ptr<const HttpBasicAuth>;

    using username_ref_t = std::string_view;
    using password_ref_t = std::string_view;

    virtual ~HttpBasicAuth() = default;

    virtual sptr_t clone() const = 0;

    virtual username_ref_t username() const = 0;
    virtual sptr_t username(username_ref_t) = 0;

    virtual password_ref_t password() const = 0;
    virtual sptr_t password(password_ref_t) = 0;
};
}
}

#endif
