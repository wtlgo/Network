#include <wtlgo/network/CurlController.hpp>
#include <gtest/gtest.h>

TEST(CurlController, IsSingleton) {
    using namespace wtlgo::network;

    ASSERT_EQ(&CurlController::instance(), &CurlController::instance());
}

TEST(CurlController, ProducesCURLInstance) {
    using namespace wtlgo::network;

    const auto test = CurlController::instance().get_handler();
    ASSERT_NE(test, nullptr);
}
