#include <gtest/gtest.h>

#include <wtlgo/network/Config.hpp>
#include <wtlgo/network/DefaultConfig.hpp>

TEST(DefaultConfig, Create) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create();
    ASSERT_NE(config, nullptr);
}
