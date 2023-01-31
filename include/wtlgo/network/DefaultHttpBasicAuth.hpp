#ifndef __WTLGO__NETWORK__DEFAULT_HTTP_BASIC_AUTH__
#define __WTLGO__NETWORK__DEFAULT_HTTP_BASIC_AUTH__

#include <memory>

#include <wtlgo/network/Auth.hpp>

namespace wtlgo {
namespace network {
class DefaultHttpBasicAuth
    : public Auth,
      public std::enable_shared_from_this<DefaultHttpBasicAuth> {
public:
    using ptr_t = std::shared_ptr<DefaultHttpBasicAuth>;
    using cptr_t = std::shared_ptr<const DefaultHttpBasicAuth>;

    virtual ~DefaultHttpBasicAuth();

    [[nodiscard]] static DefaultHttpBasicAuth::ptr_t create(
        Auth::username_ref_t username,
        Auth::password_ref_t password);

    Auth::ptr_t clone() const override;

    Auth::username_ref_t username() const override;
    Auth::ptr_t username(Auth::username_ref_t) override;

    Auth::password_ref_t password() const override;
    Auth::ptr_t password(Auth::password_ref_t) override;

protected:
    DefaultHttpBasicAuth(Auth::username_ref_t username,
                         Auth::password_ref_t password);

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;

    DefaultHttpBasicAuth(const std::unique_ptr<Impl>&);
};

using DHttpBasicAuth = DefaultHttpBasicAuth;
}
}

#endif
