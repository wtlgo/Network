#include <gtest/gtest.h>
#include "utility.hpp"

#include <string>
#include <optional>
#include <stdexcept>

#include <wtlgo/network/Config.hpp>
#include <wtlgo/network/ClientConfig.hpp>

TEST(ClientConfig, Create) {
    using namespace wtlgo::network;

    const Config::cptr_t config = ClientConfig::create();
    ASSERT_NE(config, nullptr);
}

TEST(ClientConfig, Clone) {
    using namespace wtlgo::network;

    const Config::cptr_t config = ClientConfig::create();

    const Config::cptr_t clone = config->clone();
    ASSERT_NE(clone, nullptr);
    ASSERT_NE(clone, config);
}

TEST(ClientConfig, Merge) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = ClientConfig::create();
    const Config::cptr_t rconfig = ClientConfig::create();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_NE(mconfig, nullptr);
    ASSERT_NE(mconfig, lconfig);
    ASSERT_NE(mconfig, lconfig);
}

TEST(ClientConfig, UrlSet) {
    using namespace wtlgo::network;

    const Config::ptr_t config = ClientConfig::create();

    const std::string test_url = random_string();

    ASSERT_EQ(config, config->url(test_url));
    ASSERT_EQ(config->url(), test_url);
}

TEST(ClientConfig, UrlClear) {
    using namespace wtlgo::network;

    const Config::ptr_t config =
        ClientConfig::create()->url(random_string());

    ASSERT_EQ(config, config->clear_url());
    ASSERT_EQ(config->url(), std::nullopt);
}

TEST(ClientConfig, UrlCloneEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t config = ClientConfig::create()->clear_url();
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->url(), std::nullopt);
}

TEST(ClientConfig, UrlCloneValue) {
    using namespace wtlgo::network;

    const Config::cptr_t config =
        ClientConfig::create()->url(random_string());
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->url(), config->url());
    ASSERT_NE(clone->url()->data(), config->url()->data());
}

TEST(ClientConfig, UrlMergeEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = ClientConfig::create()->clear_url();
    const Config::cptr_t rconfig = ClientConfig::create()->clear_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), std::nullopt);
}

TEST(ClientConfig, UrlMergeRight) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = ClientConfig::create()->clear_url();
    const Config::cptr_t rconfig =
        ClientConfig::create()->url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), rconfig->url());
}

TEST(ClientConfig, UrlMergeLeft) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        ClientConfig::create()->url(random_string());
    const Config::cptr_t rconfig = ClientConfig::create()->clear_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), lconfig->url());
}

TEST(ClientConfig, UrlMergeFull) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        ClientConfig::create()->url(random_string());
    const Config::cptr_t rconfig =
        ClientConfig::create()->url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), rconfig->url());
}

TEST(ClientConfig, MethodDefault) {
    using namespace wtlgo::network;

    const Config::cptr_t config = ClientConfig::create();
    ASSERT_EQ(config->method(), std::nullopt);
}

TEST(ClientConfig, MethodSet) {
    using namespace wtlgo::network;

    const Config::ptr_t config = ClientConfig::create();

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        ASSERT_EQ(config, config->method(test_method));
        ASSERT_EQ(config->method(), test_method);
    }
}

TEST(ClientConfig, MethodClear) {
    using namespace wtlgo::network;

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::ptr_t config =
            ClientConfig::create()->method(test_method);

        ASSERT_EQ(config, config->clear_method());
        ASSERT_EQ(config->method(), std::nullopt);
    }
}

TEST(ClientConfig, MethodCloneEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t config = ClientConfig::create()->clear_method();
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->method(), std::nullopt);
}

TEST(ClientConfig, MethodCloneValue) {
    using namespace wtlgo::network;

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t config =
            ClientConfig::create()->method(test_method);
        const Config::cptr_t clone = config->clone();

        ASSERT_EQ(clone->method(), test_method);
    }
}

TEST(ClientConfig, MethodMergeEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = ClientConfig::create()->clear_method();
    const Config::cptr_t rconfig = ClientConfig::create()->clear_method();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(rconfig->method(), std::nullopt);
}

TEST(ClientConfig, MethodMergeLeft) {
    using namespace wtlgo::network;

    const Config::cptr_t rconfig = ClientConfig::create()->clear_method();

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t lconfig =
            ClientConfig::create()->method(test_method);
        const Config::cptr_t mconfig = lconfig->merge(rconfig);

        ASSERT_EQ(mconfig->method(), test_method);
    }
}

TEST(ClientConfig, MethodMergeRight) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = ClientConfig::create()->clear_method();

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t rconfig =
            ClientConfig::create()->method(test_method);
        const Config::cptr_t mconfig = lconfig->merge(rconfig);

        ASSERT_EQ(mconfig->method(), test_method);
    }
}

TEST(ClientConfig, MethodMergeFull) {
    using namespace wtlgo::network;

    for (const HttpMethod ltest_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t lconfig =
            ClientConfig::create()->method(ltest_method);

        for (const HttpMethod rtest_method :
             {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH,
              HttpMethod::PUT, HttpMethod::DELETE}) {
            const Config::cptr_t rconfig =
                ClientConfig::create()->method(rtest_method);
            const Config::cptr_t mconfig = lconfig->merge(rconfig);

            ASSERT_EQ(mconfig->method(), rtest_method);
        }
    }
}

TEST(ClientConfig, BaseUrlSet) {
    using namespace wtlgo::network;

    const Config::ptr_t config = ClientConfig::create();

    const std::string test_url = random_string();

    ASSERT_EQ(config, config->base_url(test_url));
    ASSERT_EQ(config->base_url(), test_url);
}

TEST(ClientConfig, BaseUrlClear) {
    using namespace wtlgo::network;

    const Config::ptr_t config =
        ClientConfig::create()->base_url(random_string());

    ASSERT_EQ(config, config->clear_base_url());
    ASSERT_EQ(config->base_url(), std::nullopt);
}

TEST(ClientConfig, BaseUrlCloneEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t config = ClientConfig::create()->clear_base_url();
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->base_url(), std::nullopt);
}

TEST(ClientConfig, BaseUrlCloneValue) {
    using namespace wtlgo::network;

    const Config::cptr_t config =
        ClientConfig::create()->base_url(random_string());
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->base_url(), config->base_url());
    ASSERT_NE(clone->base_url()->data(), config->base_url()->data());
}

TEST(ClientConfig, BaseUrlMergeEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = ClientConfig::create()->clear_base_url();
    const Config::cptr_t rconfig = ClientConfig::create()->clear_base_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), std::nullopt);
}

TEST(ClientConfig, BaseUrlMergeRight) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = ClientConfig::create()->clear_base_url();
    const Config::cptr_t rconfig =
        ClientConfig::create()->base_url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), rconfig->base_url());
}

TEST(ClientConfig, BaseUrlMergeLeft) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        ClientConfig::create()->base_url(random_string());
    const Config::cptr_t rconfig = ClientConfig::create()->clear_base_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), lconfig->base_url());
}

TEST(ClientConfig, BaseUrlMergeFull) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        ClientConfig::create()->base_url(random_string());
    const Config::cptr_t rconfig =
        ClientConfig::create()->base_url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), rconfig->base_url());
}
