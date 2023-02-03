#include <algorithm>
#include <string>
#include <map>
#include <iterator>
#include <optional>
#include <functional>

#include <wtlgo/network/HttpHeaders.hpp>

using namespace wtlgo::network;

struct HttpHeaders::Impl {
private:
    std::map<std::string, std::string, std::less<>> _data;

public:
    Headers::key_ref_list_t keys() const {
        Headers::key_ref_list_t res;
        std::transform(
            _data.cbegin(), _data.cend(), std::inserter(res, res.begin()),
            [](const auto& val) -> Headers::key_ref_t { return val.first; });
        return res;
    }

    Headers::value_ref_opt_t get(const Headers::key_ref_t header) const {
        const auto it = _data.find(header);

        if (it == _data.cend()) {
            return std::nullopt;
        }

        return it->second;
    }

    void set(const Headers::key_ref_t header, const value_ref_t value) {
        _data.emplace(header, value);
    }

    void clear(const Headers::key_ref_t header) {
        const auto it = _data.find(header);
        if (it != _data.cend()) {
            _data.erase(it);
        }
    }
};

HttpHeaders::~HttpHeaders() = default;

HttpHeaders::ptr_t HttpHeaders::create() {
    return std::shared_ptr<HttpHeaders>{new HttpHeaders{}};
}

Headers::ptr_t HttpHeaders::clone() const {
    return std::shared_ptr<HttpHeaders>{new HttpHeaders{impl}};
}

Headers::key_ref_list_t HttpHeaders::keys() const { return impl->keys(); }

Headers::value_ref_opt_t HttpHeaders::get(
    const Headers::key_ref_t header) const {
    return impl->get(header);
}

Headers::ptr_t HttpHeaders::set(const Headers::key_ref_t header,
                                const value_ref_t value) {
    impl->set(header, value);
    return shared_from_this();
}

Headers::ptr_t HttpHeaders::erase(const Headers::key_ref_t header) {
    impl->clear(header);
    return shared_from_this();
}

HttpHeaders::HttpHeaders() : impl{std::make_unique<Impl>()} {}

HttpHeaders::HttpHeaders(const std::unique_ptr<HttpHeaders::Impl>& impl)
    : impl{std::make_unique<Impl>(*impl)} {}
