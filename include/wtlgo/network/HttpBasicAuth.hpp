#ifndef __WTLGO__NETWORK__HTTP_BASIC_AUTH_HPP__
#define __WTLGO__NETWORK__HTTP_BASIC_AUTH_HPP__

#include <string>
#include <memory>
#include <optional>
#include <functional>

namespace wtlgo {
namespace network {
class HttpBasicAuth {
public:
    using username_t = std::string;
    using password_t = std::string;

    using opt_t = std::optional<HttpBasicAuth>;

    HttpBasicAuth();
    HttpBasicAuth(const username_t& username, const password_t& password);
    HttpBasicAuth(const HttpBasicAuth&);
    virtual ~HttpBasicAuth();

    const username_t& username() const;
    HttpBasicAuth& username(const username_t& new_username);

    const password_t& password() const;
    HttpBasicAuth& password(const password_t& new_password);

private:
    struct HttpBasicAuthImpl;
    std::unique_ptr<HttpBasicAuthImpl> impl;
};
}
}

#endif
