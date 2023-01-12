#ifndef __WTLGO__NETWORK__CONFIG_HPP__
#define __WTLGO__NETWORK__CONFIG_HPP__

#include <string>
#include <memory>
#include <unordered_map>
#include <optional>
#include <functional>
#include <variant>

#include <wtlgo/network/HttpMethod.hpp>
#include <wtlgo/network/HttpBasicAuth.hpp>

namespace wtlgo {
namespace network {
class Config {
public:
    using url_t = std::string;

    using header_field_name_t = std::string;
    using header_value_t = std::string;
    using header_value_opt_ref_t =
        std::optional<std::reference_wrapper<const header_value_t>>;
    using headers_t = std::unordered_map<header_field_name_t, header_value_t>;

    using data_field_name_t = std::string;
    using data_value_t = std::variant<std::string>;
    using data_value_opt_ref_t =
        std::optional<std::reference_wrapper<const data_value_t>>;
    using data_t = std::unordered_map<data_field_name_t, data_value_t>;

    using timeout_t = unsigned long;

    Config();
    Config(const Config&);

    virtual ~Config();

    const url_t& url() const;
    Config& url(const url_t& new_url);

    HttpMethod method() const;
    Config& method(HttpMethod new_method);

    const url_t& base_url() const;
    Config& base_url(const url_t& new_base_url);

    const headers_t& headers() const;
    Config& headers(const headers_t& new_headers);

    const header_value_opt_ref_t header(const header_field_name_t& field) const;
    Config& header(const header_field_name_t& field_name,
                   const header_value_t& value);

    const data_t& data() const;
    Config& data(const data_t& new_data);

    const data_value_opt_ref_t data_field(const data_field_name_t& field) const;
    Config& data_field(const data_field_name_t& field,
                       const data_value_t& value);

    timeout_t timeout() const;
    Config& timeout(timeout_t timeout);

    const HttpBasicAuth::opt_t& auth() const;
    Config& auth(const HttpBasicAuth& auth);
    Config& auth(const HttpBasicAuth::username_t& username,
                 const HttpBasicAuth::password_t& password);
    Config& remove_auth();

private:
    struct ConfigImpl;
    std::unique_ptr<ConfigImpl> impl;
};
}
}

#endif
