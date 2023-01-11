#include <wtlgo/NetworkOld.hpp>
#include <gtest/gtest.h>

TEST(OldSanityCheck, DidInit) {
    using namespace wtlgo::old;
    ASSERT_EQ(&network, &Network::instance());
}
