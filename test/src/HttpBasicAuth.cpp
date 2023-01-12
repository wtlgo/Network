#include <wtlgo/network/HttpBasicAuth.hpp>
#include <gtest/gtest.h>
#include "utility.hpp"

TEST(HttpBasicAuth, Init) {
    using namespace wtlgo::network;

    const HttpBasicAuth::username_t test_username = random_string(50);
    const HttpBasicAuth::password_t test_password = random_string(50);

    HttpBasicAuth auth{test_username, test_password};

    ASSERT_EQ(auth.username(), test_username);
    ASSERT_EQ(auth.password(), test_password);
}

TEST(HttpBasicAuth, Username) {
    using namespace wtlgo::network;

    const HttpBasicAuth::username_t test_username = random_string(50);

    HttpBasicAuth auth;

    ASSERT_EQ(auth.username(), "");
    ASSERT_EQ(&auth.username(test_username), &auth);
    ASSERT_EQ(auth.username(), test_username);
}

TEST(HttpBasicAuth, Password) {
    using namespace wtlgo::network;

    const HttpBasicAuth::password_t test_password = random_string(50);

    HttpBasicAuth auth;

    ASSERT_EQ(auth.password(), "");
    ASSERT_EQ(&auth.password(test_password), &auth);
    ASSERT_EQ(auth.password(), test_password);
}
