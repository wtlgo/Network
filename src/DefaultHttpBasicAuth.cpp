#include <string>
#include <string_view>
#include <memory>

#include <wtlgo/network/HttpBasicAuth.hpp>
#include <wtlgo/network/DefaultHttpBasicAuth.hpp>

using namespace wtlgo::network;

struct DefaultHttpBasicAuth::Impl {
private:
    std::string _username;
    std::string _password;

public:
    Impl() = default;
    Impl(const Impl&) = default;
    Impl(const HttpBasicAuth::username_ref_t username,
         const HttpBasicAuth::password_ref_t password)
        : _username{username}, _password{password} {}

    HttpBasicAuth::username_ref_t username() const { return _username; }
    void username(const HttpBasicAuth::username_ref_t username) {
        _username = username;
    }

    HttpBasicAuth::password_ref_t password() const { return _password; }
    void password(const HttpBasicAuth::password_ref_t password) {
        _password = password;
    }
};

DefaultHttpBasicAuth::~DefaultHttpBasicAuth() = default;

DefaultHttpBasicAuth::ptr_t DefaultHttpBasicAuth::create(
    const HttpBasicAuth::username_ref_t username,
    const HttpBasicAuth::password_ref_t password) {
    return std::shared_ptr<DefaultHttpBasicAuth>(
        new DefaultHttpBasicAuth{username, password});
}

HttpBasicAuth::ptr_t DefaultHttpBasicAuth::clone() const {
    return std::shared_ptr<DefaultHttpBasicAuth>(
        new DefaultHttpBasicAuth{impl});
}

HttpBasicAuth::username_ref_t DefaultHttpBasicAuth::username() const {
    return impl->username();
}

HttpBasicAuth::ptr_t DefaultHttpBasicAuth::username(
    const HttpBasicAuth::username_ref_t username) {
    impl->username(username);
    return shared_from_this();
}

HttpBasicAuth::password_ref_t DefaultHttpBasicAuth::password() const {
    return impl->password();
}

HttpBasicAuth::ptr_t DefaultHttpBasicAuth::password(
    const HttpBasicAuth::password_ref_t password) {
    impl->password(password);
    return shared_from_this();
}

DefaultHttpBasicAuth::DefaultHttpBasicAuth(
    const HttpBasicAuth::username_ref_t username,
    const HttpBasicAuth::password_ref_t password)
    : impl{std::make_unique<Impl>(username, password)} {}

DefaultHttpBasicAuth::DefaultHttpBasicAuth(const std::unique_ptr<Impl>& impl)
    : impl{std::make_unique<Impl>(*impl)} {}
