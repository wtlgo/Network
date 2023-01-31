#include <gtest/gtest.h>
#include "utility.hpp"

#include <string>

#include <wtlgo/network/Auth.hpp>
#include <wtlgo/network/DefaultHttpBasicAuth.hpp>

TEST(DefaultHttpBasicAuth, Create) {
    using namespace wtlgo::network;

    const std::string test_username = random_string();
    const std::string test_password = random_string();

    const Auth::cptr_t client =
        DefaultHttpBasicAuth::create(test_username, test_password);

    ASSERT_NE(client, nullptr);
    ASSERT_EQ(client->username(), test_username);
    ASSERT_EQ(client->password(), test_password);
}

TEST(DefaultHttpBasicAuth, Clone) {
    using namespace wtlgo::network;

    const Auth::cptr_t client =
        DefaultHttpBasicAuth::create(random_string(), random_string());

    const Auth::cptr_t clone = client->clone();
    ASSERT_NE(clone, nullptr);
    ASSERT_NE(clone, client);

    ASSERT_EQ(client->username(), clone->username());
    ASSERT_NE(client->username().data(), clone->username().data());

    ASSERT_EQ(client->password(), clone->password());
    ASSERT_NE(client->password().data(), clone->password().data());
}

TEST(DefaultHttpBasicAuth, SetUsername) {
    using namespace wtlgo::network;

    const Auth::ptr_t client =
        DefaultHttpBasicAuth::create(random_string(), random_string());

    const std::string test_username = random_string();
    ASSERT_EQ(client, client->username(test_username));
    ASSERT_EQ(client->username(), test_username);
}

TEST(DefaultHttpBasicAuth, SetPassword) {
    using namespace wtlgo::network;

    const Auth::ptr_t client =
        DefaultHttpBasicAuth::create(random_string(), random_string());

    const std::string test_password = random_string();
    ASSERT_EQ(client, client->password(test_password));
    ASSERT_EQ(client->password(), test_password);
}
