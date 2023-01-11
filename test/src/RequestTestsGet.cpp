#include <wtlgo/NetworkOld.hpp>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>

#include "utility.hpp"

TEST(Request, Get_NoSSL_Static) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    const string response =
        network.request("http://" + test_server + "/get", {{"hello", "hello"}});

    ASSERT_NO_THROW({
        auto resp = json::parse(response);
        ASSERT_EQ(resp["args"]["hello"], "hello");
    });
}

TEST(Request, Get_SSL_Static) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    const string response = network.request("https://" + test_server + "/get",
                                            {{"hello", "hello"}});
    ASSERT_NO_THROW({
        auto resp = json::parse(response);
        ASSERT_EQ(resp["args"]["hello"], "hello");
    });
}

TEST(Request, Get_NoSSL_Random) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    ASSERT_NO_THROW({
        const string arg = random_string(500);
        const string val = random_string(1000);

        const string response =
            network.request("http://" + test_server + "/get", {{arg, val}});

        const auto resp = json::parse(response);

        ASSERT_EQ(resp["args"][arg], val);
    });
}

TEST(Request, Get_SSL_Random) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;

    ASSERT_NO_THROW({
        const string arg = random_string(500);
        const string val = random_string(500);

        const string response =
            network.request("https://" + test_server + "/get", {{arg, val}});
        const auto resp = json::parse(response);

        ASSERT_EQ(resp["args"][arg], val);
    });
}

TEST(Request, Get_NoSSL_Random_MultipleArgs) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;
    using map = std::map<string, string>;

    map args;
    for (size_t i = 0; i < 10; ++i) {
        args[random_string(50)] = random_string(50);
    }

    ASSERT_NO_THROW({
        const string response =
            network.request("http://" + test_server + "/get", args);
        const auto resp = json::parse(response);

        for (const auto& arg : args) {
            ASSERT_EQ(resp["args"][arg.first], arg.second);
        }
    });
}

TEST(Request, Get_SSL_Random_MultipleArgs) {
    using namespace wtlgo::old;
    using json = nlohmann::json;
    using string = std::string;
    using map = std::map<string, string>;

    map args;
    for (size_t i = 0; i < 10; ++i) {
        args[random_string(50)] = random_string(50);
    }

    ASSERT_NO_THROW({
        const string response =
            network.request("https://" + test_server + "/get", args);

        const auto resp = json::parse(response);

        for (const auto& arg : args) {
            ASSERT_EQ(resp["args"][arg.first], arg.second);
        }
    });
}
