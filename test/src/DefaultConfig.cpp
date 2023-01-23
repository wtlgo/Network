#include <gtest/gtest.h>
#include "utility.hpp"

#include <string>
#include <optional>
#include <stdexcept>

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

TEST(DefaultConfig, Merge) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create();
    const Config::cptr_t rconfig = DefaultConfig::create();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_NE(mconfig, nullptr);
    ASSERT_NE(mconfig, lconfig);
    ASSERT_NE(mconfig, lconfig);
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
    ASSERT_NE(clone->url()->data(), config->url()->data());
}

TEST(DefaultConfig, UrlMergeEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t rconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), std::nullopt);
}

TEST(DefaultConfig, UrlMergeRight) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t rconfig =
        DefaultConfig::create()->url(random_string(50));
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), rconfig->url());
}

TEST(DefaultConfig, UrlMergeLeft) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        DefaultConfig::create()->url(random_string(50));
    const Config::cptr_t rconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), lconfig->url());
}

TEST(DefaultConfig, UrlMergeFull) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        DefaultConfig::create()->url(random_string(50));
    const Config::cptr_t rconfig =
        DefaultConfig::create()->url(random_string(50));
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), rconfig->url());
}
