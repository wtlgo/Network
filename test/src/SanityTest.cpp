#include <wtlgo/Network.hpp>
#include <gtest/gtest.h>

TEST(SanityCheck, DidInit) {
    using namespace wtlgo::old;
    ASSERT_EQ(&network, &Network::instance());
}
