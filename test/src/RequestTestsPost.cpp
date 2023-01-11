#include <wtlgo/Network.hpp>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>

#include "utility.hpp"

TEST(Request, Post_NoSSL_Static) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    const string response = network.request("http://" + test_server + "/post",
                                            {{"hello", "hello"}}, true);
    ASSERT_NO_THROW({
        auto resp = json::parse(response);
        ASSERT_EQ(resp["form"]["hello"], "hello");
    });
}

TEST(Request, Post_SSL_Static) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    const string response = network.request("https://" + test_server + "/post",
                                            {{"hello", "hello"}}, true);
    ASSERT_NO_THROW({
        const auto resp = json::parse(response);
        ASSERT_EQ(resp["form"]["hello"], "hello");
    });
}

TEST(Request, Post_NoSSL_Random) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    ASSERT_NO_THROW({
        const string arg = random_string(1000);
        const string val = random_string(1000);

        const string response = network.request(
            "http://" + test_server + "/post", {{arg, val}}, true);
        const auto resp = json::parse(response);

        ASSERT_EQ(resp["form"][arg], val);
    });
}

TEST(Request, Post_SSL_Random) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    ASSERT_NO_THROW({
        const string arg = random_string(1000);
        const string val = random_string(1000);

        const string response = network.request(
            "https://" + test_server + "/post", {{arg, val}}, true);

        const auto resp = json::parse(response);

        ASSERT_EQ(resp["form"][arg], val);
    });
}

TEST(Request, Post_NoSSL_Random_MultipleArgs) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;
    using map = std::map<string, string>;

    map args;
    for (size_t i = 0; i < 10; ++i) {
        args[random_string(1000)] = random_string(1000);
    }

    ASSERT_NO_THROW({
        const string response =
            network.request("http://" + test_server + "/post", args, true);
        const auto resp = json::parse(response);

        for (const auto& arg : args) {
            ASSERT_EQ(resp["form"][arg.first], arg.second);
        }
    });
}

TEST(Request, Post_SSL_Random_MultipleArgs) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;
    using map = std::map<string, string>;

    map args;
    for (size_t i = 0; i < 10; ++i) {
        args[random_string(1000)] = random_string(1000);
    }

    const string response =
        network.request("https://" + test_server + "/post", args, true);

    ASSERT_NO_THROW({
        const auto resp = json::parse(response);

        for (const auto& arg : args) {
            ASSERT_EQ(resp["form"][arg.first], arg.second);
        }
    });
}
