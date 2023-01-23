#include <gtest/gtest.h>
#include "utility.hpp"

#include <string>
#include <optional>

#include <wtlgo/network/Config.hpp>
#include <wtlgo/network/DefaultConfig.hpp>

TEST(DefaultConfig, Create) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create();
    ASSERT_NE(config, nullptr);
}

TEST(DefaultConfig, Clone) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create();

    const Config::cptr_t clone = config->clone();
    ASSERT_NE(clone, nullptr);
    ASSERT_NE(clone, config);
}

TEST(DefaultConfig, UrlSet) {
    using namespace wtlgo::network;

    const Config::ptr_t config = DefaultConfig::create();

    const std::string test_url = random_string(50);

    ASSERT_EQ(config, config->url(test_url));
    ASSERT_EQ(config->url(), test_url);
}

TEST(DefaultConfig, UrlClear) {
    using namespace wtlgo::network;

    const Config::ptr_t config =
        DefaultConfig::create()->url(random_string(50));

    ASSERT_EQ(config, config->clear_url());
    ASSERT_EQ(config->url(), std::nullopt);
}

TEST(DefaultConfig, UrlCloneEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create()->clear_url();
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->url(), std::nullopt);
}

TEST(DefaultConfig, UrlCloneValue) {
    using namespace wtlgo::network;

    const Config::cptr_t config =
        DefaultConfig::create()->url(random_string(50));
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->url(), config->url());
    ASSERT_NE(clone->url().value().data(), config->url().value().data());
}
