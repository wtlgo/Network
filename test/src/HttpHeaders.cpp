#include <gtest/gtest.h>
#include "utility.hpp"

#include <algorithm>
#include <optional>
#include <string>
#include <set>
#include <iterator>
#include <string_view>

#include <wtlgo/network/Headers.hpp>
#include <wtlgo/network/HttpHeaders.hpp>

TEST(HttpHeaders, Create) {
    using namespace wtlgo::network;

    const Headers::cptr_t headers = HttpHeaders::create();
    ASSERT_NE(headers, nullptr);
}

TEST(HttpHeaders, Clone) {
    using namespace wtlgo::network;

    const Headers::ptr_t headers = HttpHeaders::create();
    for (std::size_t i = 0; i < 50; ++i) {
        headers->set(random_string(), random_string());
    }

    Headers::cptr_t clone = headers->clone();

    ASSERT_NE(clone, nullptr);
    ASSERT_NE(clone, headers);

    for (const auto& header : headers->keys()) {
        ASSERT_EQ(headers->get(header), clone->get(header));
        ASSERT_NE(headers->get(header)->data(), clone->get(header)->data());
    }
}

TEST(HttpHeaders, Set) {
    using namespace wtlgo::network;

    const Headers::ptr_t headers = HttpHeaders::create();

    const std::string key = random_string();
    const std::string value = random_string();

    ASSERT_EQ(headers, headers->set(key, value));
    ASSERT_NE(headers->get(key), std::nullopt);
    ASSERT_EQ(headers->get(key), value);
}

TEST(HttpHeaders, Erase) {
    using namespace wtlgo::network;

    const std::string key = random_string();
    Headers::ptr_t headers = HttpHeaders::create()->set(key, random_string());

    ASSERT_EQ(headers, headers->erase(key));
    ASSERT_EQ(headers->get(key), std::nullopt);
}

TEST(HttpHeaders, Keys) {
    using namespace wtlgo::network;

    const std::set<std::string> keys = [] {
        std::set<std::string> res;
        std::generate_n(std::inserter(res, res.begin()),
                        random_unsigned() % 100,
                        []() { return random_string(); });
        return res;
    }();

    const Headers::ptr_t headers = HttpHeaders::create();
    for (const auto& header : keys) {
        headers->set(header, random_string());
    }

    const std::set<std::string_view> ref_keys = [&keys] {
        std::set<std::string_view> res;
        std::copy(keys.cbegin(), keys.cend(), std::inserter(res, res.begin()));
        return res;
    }();

    ASSERT_EQ(ref_keys, headers->keys());
}
