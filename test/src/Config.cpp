#include <wtlgo/network/Config.hpp>
#include <gtest/gtest.h>
#include <string>
#include "utility.hpp"

TEST(Config, Url) {
    using namespace wtlgo::network;

    Config config;

    ASSERT_EQ(config.url(), "");

    const std::string test_url = random_string(42);
    ASSERT_EQ(&config.url(test_url), &config);

    ASSERT_EQ(config.url(), test_url);
}

TEST(Config, Method) {
    using namespace wtlgo::network;

    Config config;

    ASSERT_EQ(config.method(), HttpMethod::GET);

    for (const HttpMethod test_method :
         {HttpMethod::POST, HttpMethod::PUT, HttpMethod::PATCH,
          HttpMethod::DELETE, HttpMethod::GET}) {
        ASSERT_EQ(&config.method(test_method), &config);
        ASSERT_EQ(config.method(), test_method);
    }
}

TEST(Config, BaseUrl) {
    using namespace wtlgo::network;

    Config config;

    ASSERT_EQ(config.base_url(), "");

    const std::string test_base_url = random_string(42);
    ASSERT_EQ(&config.base_url(test_base_url), &config);

    ASSERT_EQ(config.base_url(), test_base_url);
}

TEST(Config, HeadersAll) {
    using namespace wtlgo::network;

    Config config;

    ASSERT_EQ(config.headers().size(), 0);

    Config::headers_t test_headers;
    for (std::size_t i = 0; i < 10; ++i) {
        test_headers[random_string(50)] = random_string(50);
    }

    ASSERT_EQ(&config.headers(test_headers), &config);
    ASSERT_EQ(config.headers().size(), test_headers.size());

    for (const auto & [ test_field_name, test_value ] : test_headers) {
        const auto& headers = config.headers();
        const auto field = headers.find(test_field_name);
        ASSERT_NE(field, headers.cend());

        ASSERT_EQ(field->first, test_field_name);
        ASSERT_EQ(field->second, test_value);
    }
}

TEST(Config, HeadersSingle) {
    using namespace wtlgo::network;

    Config config;

    Config::header_field_name_t none_name;
    for (std::size_t i = 0; i < 10; ++i) {
        const Config::header_field_name_t test_field_name =
            random_string(10, true);
        const Config::header_value_t test_value = random_string(50);

        none_name.push_back(1 + (127 - 1 + test_field_name.at(i)) % (127 - 1));

        ASSERT_EQ(&config.header(test_field_name, test_value), &config);

        const auto real_value = config.header(test_field_name);
        ASSERT_EQ(real_value.has_value(), true);
        ASSERT_EQ(real_value.value().get(), test_value);
    }
}