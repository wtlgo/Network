#include <memory>

#include <wtlgo/network/HttpBasicAuth.hpp>

using namespace wtlgo::network;

struct HttpBasicAuth::HttpBasicAuthImpl {
    username_t _username;
    password_t _password;

    HttpBasicAuthImpl() = default;
    HttpBasicAuthImpl(const username_t& username, const password_t& password)
        : _username{username}, _password{password} {}

    const username_t& username() const { return _username; }
    void username(const username_t& new_username) { _username = new_username; }

    const username_t& password() const { return _password; }
    void password(const password_t& new_password) { _password = new_password; }
};

HttpBasicAuth::HttpBasicAuth() : impl{std::make_unique<HttpBasicAuthImpl>()} {}
HttpBasicAuth::HttpBasicAuth(const username_t& username,
                             const password_t& password)
    : impl{std::make_unique<HttpBasicAuthImpl>(username, password)} {}
HttpBasicAuth::~HttpBasicAuth() = default;

const HttpBasicAuth::username_t& HttpBasicAuth::username() const {
    return impl->username();
}

HttpBasicAuth& HttpBasicAuth::username(
    const HttpBasicAuth::username_t& new_username) {
    impl->username(new_username);
    return *this;
}

const HttpBasicAuth::password_t& HttpBasicAuth::password() const {
    return impl->password();
}

HttpBasicAuth& HttpBasicAuth::password(
    const HttpBasicAuth::password_t& new_password) {
    impl->password(new_password);
    return *this;
}
