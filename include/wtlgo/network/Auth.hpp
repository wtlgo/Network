#ifndef __WTLGO__NETWORK__AUTH__
#define __WTLGO__NETWORK__AUTH__

#include <memory>
#include <string_view>

namespace wtlgo {
namespace network {
struct Auth {
    using ptr_t = std::shared_ptr<Auth>;
    using cptr_t = std::shared_ptr<const Auth>;

    using username_ref_t = std::string_view;
    using password_ref_t = std::string_view;

    virtual ~Auth() = default;

    virtual ptr_t clone() const = 0;

    virtual username_ref_t username() const = 0;
    virtual ptr_t username(username_ref_t) = 0;

    virtual password_ref_t password() const = 0;
    virtual ptr_t password(password_ref_t) = 0;
};
}
}

#endif
