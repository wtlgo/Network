#include <wtlgo/Network.hpp>
#include <gtest/gtest.h>

TEST(Primary, DidInit)
{
    using namespace wtlgo;
    ASSERT_EQ(&network, &Network::instance());
}
