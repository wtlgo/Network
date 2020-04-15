#include <wtlgo/Network.hpp>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <string>

TEST(Primary, DidInit)
{
    using namespace wtlgo;

    ASSERT_NE(&network, nullptr);
    ASSERT_EQ(&network, &Network::instance());
}

const std::string test_server = "httpbin.org";

TEST(Request, Get_NoSSL_Static)
{
    using namespace wtlgo;
    using json = nlohmann::json;
    using string = std::string;
    
    string response = network.request("http://" + test_server + "/get", {{"hello", "hello"}});
    ASSERT_NO_THROW({
        auto resp = json::parse(response);
        ASSERT_EQ(resp["args"]["hello"], "hello");
    });
}

TEST(Request, Get_SSL_Static)
{
    using namespace wtlgo;
    using json = nlohmann::json;
    using string = std::string;
    
    string response = network.request("https://" + test_server + "/get", {{"hello", "hello"}});
    ASSERT_NO_THROW({
        auto resp = json::parse(response);
        ASSERT_EQ(resp["args"]["hello"], "hello");
    });
}

#include <random>
std::string random_string(size_t max_length) {
    static std::mt19937_64 engine { (std::random_device())() };
    std::uniform_int_distribution<size_t> sdist(0, max_length);
    std::uniform_int_distribution<char> cdist(0, 127);

    std::string out;
    std::generate_n(std::back_inserter(out), sdist(engine), [&cdist]{ return cdist(engine); });
    return out;
}

TEST(Request, Get_NoSSL_Random)
{
    using namespace wtlgo;
    using json = nlohmann::json;
    using string = std::string;
    
    ASSERT_NO_THROW({
        for(size_t i = 0; i < 10; i++) {
            const string arg = random_string(500);
            const string val = random_string(1000);
            
            string response = network.request("http://" + test_server + "/get", {{arg, val}});
            auto resp = json::parse(response);

            ASSERT_EQ(resp["args"][arg], val) << response;
        }
    });
}

TEST(Request, Get_SSL_Random)
{
    using namespace wtlgo;
    using json = nlohmann::json;
    using string = std::string;
    
    ASSERT_NO_THROW({
        for(size_t i = 0; i < 10; i++) {
            const string arg = random_string(500);
            const string val = random_string(500);
            
            string response = network.request("https://" + test_server + "/get", {{arg, val}});
            auto resp = json::parse(response);

            ASSERT_EQ(resp["args"][arg], val);
        }
    });
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}