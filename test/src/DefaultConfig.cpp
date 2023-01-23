#include <gtest/gtest.h>

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
    ASSERT_NE(config, nullptr);

    const Config::cptr_t clone = config->clone();
    ASSERT_NE(clone, nullptr);
    ASSERT_NE(clone, config);
}