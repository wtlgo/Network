#ifndef __WTLGO__NETWORK__DEFAULT_HTTP_BASIC_AUTH__
#define __WTLGO__NETWORK__DEFAULT_HTTP_BASIC_AUTH__

#include <memory>

#include <wtlgo/network/HttpBasicAuth.hpp>

namespace wtlgo {
namespace network {
class DefaultHttpBasicAuth
    : public HttpBasicAuth,
      public std::enable_shared_from_this<DefaultHttpBasicAuth> {
public:
    using sptr_t = std::shared_ptr<DefaultHttpBasicAuth>;
    using csptr_t = std::shared_ptr<const DefaultHttpBasicAuth>;

    ~DefaultHttpBasicAuth();

    [[nodiscard]] static DefaultHttpBasicAuth::sptr_t create(
        HttpBasicAuth::username_ref_t username,
        HttpBasicAuth::password_ref_t password);

    HttpBasicAuth::sptr_t clone() const override;

    HttpBasicAuth::username_ref_t username() const override;
    HttpBasicAuth::sptr_t username(HttpBasicAuth::username_ref_t) override;

    HttpBasicAuth::password_ref_t password() const override;
    HttpBasicAuth::sptr_t password(HttpBasicAuth::password_ref_t) override;

protected:
    DefaultHttpBasicAuth(HttpBasicAuth::username_ref_t username,
                         HttpBasicAuth::password_ref_t password);

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;

    DefaultHttpBasicAuth(const std::unique_ptr<Impl>&);
};

using DHttpBasicAuth = DefaultHttpBasicAuth;
}
}

#endif
