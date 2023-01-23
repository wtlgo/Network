#include <memory>
#include <string>
#include <optional>
#include <stdexcept>
#include <utility>

#include <wtlgo/network/Config.hpp>
#include <wtlgo/network/DefaultConfig.hpp>

using namespace wtlgo::network;

struct DefaultConfig::Impl {
private:
    std::optional<std::string> _url;

public:
    std::unique_ptr<Impl> merge(const Config::cptr_t rconfig) const {
        if (rconfig == nullptr) {
            throw std::invalid_argument{"nullptr is provided!"};
        }

        auto res = std::make_unique<Impl>(*this);

        if (rconfig->url()) {
            res->_url = rconfig->url();
        }

        return res;
    }

    Config::url_opt_ref_t url() const { return _url; }
    void url(const Config::url_ref_t url) { _url = url; }
    void clear_url() { _url = std::nullopt; }
};

DefaultConfig::~DefaultConfig() = default;

DefaultConfig::ptr_t DefaultConfig::create() {
    return std::shared_ptr<DefaultConfig>{new DefaultConfig{}};
}

Config::ptr_t DefaultConfig::clone() const {
    return std::shared_ptr<DefaultConfig>{new DefaultConfig{impl}};
}

Config::ptr_t DefaultConfig::merge(const Config::cptr_t rconfig) const {
    return std::shared_ptr<DefaultConfig>{
        new DefaultConfig{impl->merge(rconfig)}};
}

Config::url_opt_ref_t DefaultConfig::url() const { return impl->url(); }

Config::ptr_t DefaultConfig::url(const Config::url_ref_t url) {
    impl->url(url);
    return shared_from_this();
}

Config::ptr_t DefaultConfig::clear_url() {
    impl->clear_url();
    return shared_from_this();
}

DefaultConfig::DefaultConfig() : impl{std::make_unique<Impl>()} {}

DefaultConfig::DefaultConfig(const std::unique_ptr<Impl>& impl)
    : impl{std::make_unique<Impl>(*impl)} {}

DefaultConfig::DefaultConfig(std::unique_ptr<Impl>&& impl)
    : impl{std::move(impl)} {}
