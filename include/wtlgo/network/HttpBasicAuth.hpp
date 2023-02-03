#ifndef __WTLGO__NETWORK__DEFAULT_HTTP_BASIC_AUTH__
#define __WTLGO__NETWORK__DEFAULT_HTTP_BASIC_AUTH__

#include <memory>

#include <wtlgo/network/Auth.hpp>

namespace wtlgo {
namespace network {
class HttpBasicAuth : public Auth,
                      public std::enable_shared_from_this<HttpBasicAuth> {
public:
    using ptr_t = std::shared_ptr<HttpBasicAuth>;
    using cptr_t = std::shared_ptr<const HttpBasicAuth>;

    virtual ~HttpBasicAuth();

    [[nodiscard]] static HttpBasicAuth::ptr_t create(
        Auth::username_ref_t username, Auth::password_ref_t password);

    Auth::ptr_t clone() const override;

    Auth::username_ref_t username() const override;
    Auth::ptr_t username(Auth::username_ref_t) override;

    Auth::password_ref_t password() const override;
    Auth::ptr_t password(Auth::password_ref_t) override;

protected:
    HttpBasicAuth(Auth::username_ref_t username, Auth::password_ref_t password);

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;

    HttpBasicAuth(const std::unique_ptr<Impl>&);
};
}
}

#endif
