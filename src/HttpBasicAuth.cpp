#include <string>
#include <string_view>
#include <memory>

#include <wtlgo/network/Auth.hpp>
#include <wtlgo/network/HttpBasicAuth.hpp>

using namespace wtlgo::network;

struct HttpBasicAuth::Impl {
private:
    std::string _username;
    std::string _password;

public:
    Impl() = default;
    Impl(const Impl&) = default;
    Impl(const Auth::username_ref_t username,
         const Auth::password_ref_t password)
        : _username{username}, _password{password} {}

    Auth::username_ref_t username() const { return _username; }
    void username(const Auth::username_ref_t username) {
        _username = username;
    }

    Auth::password_ref_t password() const { return _password; }
    void password(const Auth::password_ref_t password) {
        _password = password;
    }
};

HttpBasicAuth::~HttpBasicAuth() = default;

HttpBasicAuth::ptr_t HttpBasicAuth::create(
    const Auth::username_ref_t username,
    const Auth::password_ref_t password) {
    return std::shared_ptr<HttpBasicAuth>(
        new HttpBasicAuth{username, password});
}

Auth::ptr_t HttpBasicAuth::clone() const {
    return std::shared_ptr<HttpBasicAuth>(
        new HttpBasicAuth{impl});
}

Auth::username_ref_t HttpBasicAuth::username() const {
    return impl->username();
}

Auth::ptr_t HttpBasicAuth::username(
    const Auth::username_ref_t username) {
    impl->username(username);
    return shared_from_this();
}

Auth::password_ref_t HttpBasicAuth::password() const {
    return impl->password();
}

Auth::ptr_t HttpBasicAuth::password(
    const Auth::password_ref_t password) {
    impl->password(password);
    return shared_from_this();
}

HttpBasicAuth::HttpBasicAuth(
    const Auth::username_ref_t username,
    const Auth::password_ref_t password)
    : impl{std::make_unique<Impl>(username, password)} {}

HttpBasicAuth::HttpBasicAuth(const std::unique_ptr<Impl>& impl)
    : impl{std::make_unique<Impl>(*impl)} {}
