#include <gtest/gtest.h>

#include <wtlgo/network/Client.hpp>
#include <wtlgo/network/CurlClient.hpp>

TEST(CurlClient, Create) {
    using namespace wtlgo::network;

    const Client::cptr_t client = CurlClient::create();
    ASSERT_NE(client, nullptr);
}

TEST(CurlClient, InitConfig) {
    using namespace wtlgo::network;

    const Client::cptr_t client = CurlClient::create();
    ASSERT_NE(client->config(), nullptr);
}
