#include <gtest/gtest.h>
#include "utility.hpp"

#include <string>
#include <optional>
#include <stdexcept>

#include <wtlgo/network/Config.hpp>
#include <wtlgo/network/DefaultConfig.hpp>

TEST(DefaultConfig, Create) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create();
    ASSERT_NE(config, nullptr);
}

TEST(DefaultConfig, Clone) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create();

    const Config::cptr_t clone = config->clone();
    ASSERT_NE(clone, nullptr);
    ASSERT_NE(clone, config);
}

TEST(DefaultConfig, Merge) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create();
    const Config::cptr_t rconfig = DefaultConfig::create();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_NE(mconfig, nullptr);
    ASSERT_NE(mconfig, lconfig);
    ASSERT_NE(mconfig, lconfig);
}

TEST(DefaultConfig, UrlSet) {
    using namespace wtlgo::network;

    const Config::ptr_t config = DefaultConfig::create();

    const std::string test_url = random_string();

    ASSERT_EQ(config, config->url(test_url));
    ASSERT_EQ(config->url(), test_url);
}

TEST(DefaultConfig, UrlClear) {
    using namespace wtlgo::network;

    const Config::ptr_t config =
        DefaultConfig::create()->url(random_string());

    ASSERT_EQ(config, config->clear_url());
    ASSERT_EQ(config->url(), std::nullopt);
}

TEST(DefaultConfig, UrlCloneEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create()->clear_url();
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->url(), std::nullopt);
}

TEST(DefaultConfig, UrlCloneValue) {
    using namespace wtlgo::network;

    const Config::cptr_t config =
        DefaultConfig::create()->url(random_string());
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->url(), config->url());
    ASSERT_NE(clone->url()->data(), config->url()->data());
}

TEST(DefaultConfig, UrlMergeEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t rconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), std::nullopt);
}

TEST(DefaultConfig, UrlMergeRight) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t rconfig =
        DefaultConfig::create()->url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), rconfig->url());
}

TEST(DefaultConfig, UrlMergeLeft) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        DefaultConfig::create()->url(random_string());
    const Config::cptr_t rconfig = DefaultConfig::create()->clear_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), lconfig->url());
}

TEST(DefaultConfig, UrlMergeFull) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        DefaultConfig::create()->url(random_string());
    const Config::cptr_t rconfig =
        DefaultConfig::create()->url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->url(), rconfig->url());
}

TEST(DefaultConfig, MethodDefault) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create();
    ASSERT_EQ(config->method(), std::nullopt);
}

TEST(DefaultConfig, MethodSet) {
    using namespace wtlgo::network;

    const Config::ptr_t config = DefaultConfig::create();

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        ASSERT_EQ(config, config->method(test_method));
        ASSERT_EQ(config->method(), test_method);
    }
}

TEST(DefaultConfig, MethodClear) {
    using namespace wtlgo::network;

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::ptr_t config =
            DefaultConfig::create()->method(test_method);

        ASSERT_EQ(config, config->clear_method());
        ASSERT_EQ(config->method(), std::nullopt);
    }
}

TEST(DefaultConfig, MethodCloneEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create()->clear_method();
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->method(), std::nullopt);
}

TEST(DefaultConfig, MethodCloneValue) {
    using namespace wtlgo::network;

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t config =
            DefaultConfig::create()->method(test_method);
        const Config::cptr_t clone = config->clone();

        ASSERT_EQ(clone->method(), test_method);
    }
}

TEST(DefaultConfig, MethodMergeEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_method();
    const Config::cptr_t rconfig = DefaultConfig::create()->clear_method();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(rconfig->method(), std::nullopt);
}

TEST(DefaultConfig, MethodMergeLeft) {
    using namespace wtlgo::network;

    const Config::cptr_t rconfig = DefaultConfig::create()->clear_method();

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t lconfig =
            DefaultConfig::create()->method(test_method);
        const Config::cptr_t mconfig = lconfig->merge(rconfig);

        ASSERT_EQ(mconfig->method(), test_method);
    }
}

TEST(DefaultConfig, MethodMergeRight) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_method();

    for (const HttpMethod test_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t rconfig =
            DefaultConfig::create()->method(test_method);
        const Config::cptr_t mconfig = lconfig->merge(rconfig);

        ASSERT_EQ(mconfig->method(), test_method);
    }
}

TEST(DefaultConfig, MethodMergeFull) {
    using namespace wtlgo::network;

    for (const HttpMethod ltest_method :
         {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH, HttpMethod::PUT,
          HttpMethod::DELETE}) {
        const Config::cptr_t lconfig =
            DefaultConfig::create()->method(ltest_method);

        for (const HttpMethod rtest_method :
             {HttpMethod::GET, HttpMethod::POST, HttpMethod::PATCH,
              HttpMethod::PUT, HttpMethod::DELETE}) {
            const Config::cptr_t rconfig =
                DefaultConfig::create()->method(rtest_method);
            const Config::cptr_t mconfig = lconfig->merge(rconfig);

            ASSERT_EQ(mconfig->method(), rtest_method);
        }
    }
}

TEST(DefaultConfig, BaseUrlSet) {
    using namespace wtlgo::network;

    const Config::ptr_t config = DefaultConfig::create();

    const std::string test_url = random_string();

    ASSERT_EQ(config, config->base_url(test_url));
    ASSERT_EQ(config->base_url(), test_url);
}

TEST(DefaultConfig, BaseUrlClear) {
    using namespace wtlgo::network;

    const Config::ptr_t config =
        DefaultConfig::create()->base_url(random_string());

    ASSERT_EQ(config, config->clear_base_url());
    ASSERT_EQ(config->base_url(), std::nullopt);
}

TEST(DefaultConfig, BaseUrlCloneEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t config = DefaultConfig::create()->clear_base_url();
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->base_url(), std::nullopt);
}

TEST(DefaultConfig, BaseUrlCloneValue) {
    using namespace wtlgo::network;

    const Config::cptr_t config =
        DefaultConfig::create()->base_url(random_string());
    const Config::cptr_t clone = config->clone();

    ASSERT_EQ(clone->base_url(), config->base_url());
    ASSERT_NE(clone->base_url()->data(), config->base_url()->data());
}

TEST(DefaultConfig, BaseUrlMergeEmpty) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_base_url();
    const Config::cptr_t rconfig = DefaultConfig::create()->clear_base_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), std::nullopt);
}

TEST(DefaultConfig, BaseUrlMergeRight) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig = DefaultConfig::create()->clear_base_url();
    const Config::cptr_t rconfig =
        DefaultConfig::create()->base_url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), rconfig->base_url());
}

TEST(DefaultConfig, BaseUrlMergeLeft) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        DefaultConfig::create()->base_url(random_string());
    const Config::cptr_t rconfig = DefaultConfig::create()->clear_base_url();
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), lconfig->base_url());
}

TEST(DefaultConfig, BaseUrlMergeFull) {
    using namespace wtlgo::network;

    const Config::cptr_t lconfig =
        DefaultConfig::create()->base_url(random_string());
    const Config::cptr_t rconfig =
        DefaultConfig::create()->base_url(random_string());
    const Config::cptr_t mconfig = lconfig->merge(rconfig);

    ASSERT_EQ(mconfig->base_url(), rconfig->base_url());
}
