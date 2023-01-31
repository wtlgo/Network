#ifndef __WTLGO__NETWORK__HEADERS__
#define __WTLGO__NETWORK__HEADERS__

#include <memory>
#include <string_view>
#include <set>
#include <optional>

namespace wtlgo {
namespace network {
struct Headers {
    using ptr_t = std::shared_ptr<Headers>;
    using cptr_t = std::shared_ptr<const Headers>;

    virtual ~Headers() = default;

    using key_ref_t = std::string_view;
    using key_ref_list_t = std::set<key_ref_t>;

    using value_ref_t = std::string_view;
    using value_ref_opt_t = std::optional<value_ref_t>;

    virtual ptr_t clone() const = 0;

    virtual key_ref_list_t keys() const = 0;
    virtual value_ref_opt_t get(key_ref_t header) const = 0;
    virtual ptr_t set(key_ref_t header, value_ref_t value) = 0;
    virtual ptr_t erase(key_ref_t header) = 0;
};
}
}

#endif
