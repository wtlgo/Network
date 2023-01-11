#ifndef __WTLGO__NETWORK__CONFIG_HPP__
#define __WTLGO__NETWORK__CONFIG_HPP__

#include <string>
#include <memory>
#include <unordered_map>
#include <optional>
#include <functional>
#include <variant>

#include <wtlgo/network/HttpMethod.hpp>

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
    using data_t = std::unordered_map<data_field_name_t, data_value_t>;

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

private:
    struct ConfigImpl;
    std::unique_ptr<ConfigImpl> impl;
};
}
}

#endif
