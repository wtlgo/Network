#include <wtlgo/Network.hpp>
#include <gtest/gtest.h>

TEST(Primary, DidInit)
{
    using namespace wtlgo;
    ASSERT_NE(&network, nullptr);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}