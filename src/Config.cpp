#include <memory>
#include <optional>

#include <wtlgo/network/HttpMethod.hpp>
#include <wtlgo/network/Config.hpp>

using namespace wtlgo::network;

struct Config::ConfigImpl {
    url_t _url;
    const url_t& url() const { return _url; }
    void url(const url_t& new_url) { _url = new_url; }

    HttpMethod _method = HttpMethod::GET;
    HttpMethod method() const { return _method; }
    void method(const HttpMethod new_method) { _method = new_method; }

    url_t _base_url;
    const url_t& base_url() const { return _base_url; }
    void base_url(const url_t& new_base_url) { _base_url = new_base_url; }

    headers_t _headers;
    const headers_t& headers() const { return _headers; }
    void headers(const headers_t& new_headers) { _headers = new_headers; }

    const header_value_opt_ref_t header(
        const header_field_name_t& field_name) const {
        const auto field = _headers.find(field_name);

        if (field == _headers.cend()) {
            return std::nullopt;
        }

        return std::cref(field->second);
    }

    void header(const header_field_name_t& field_name,
                const header_value_t& value) {
        _headers[field_name] = value;
    }
};

Config::Config() : impl{std::make_unique<ConfigImpl>()} {}
Config::Config(const Config& conf)
    : impl{std::make_unique<ConfigImpl>(*conf.impl)} {}

Config::~Config() = default;

const Config::url_t& Config::url() const { return impl->url(); }
Config& Config::url(const Config::url_t& new_url) {
    impl->url(new_url);
    return *this;
}

HttpMethod Config::method() const { return impl->method(); }
Config& Config::method(const HttpMethod new_method) {
    impl->method(new_method);
    return *this;
}

const Config::url_t& Config::base_url() const { return impl->base_url(); }
Config& Config::base_url(const Config::url_t& new_base_url) {
    impl->base_url(new_base_url);
    return *this;
}

const Config::headers_t& Config::headers() const { return impl->headers(); }
Config& Config::headers(const Config::headers_t& new_headers) {
    impl->headers(new_headers);
    return *this;
}

const Config::header_value_opt_ref_t Config::header(
    const Config::header_field_name_t& field) const {
    return impl->header(field);
}

Config& Config::header(const Config::header_field_name_t& field_name,
                       const Config::header_value_t& value) {
    impl->header(field_name, value);
    return *this;
}
