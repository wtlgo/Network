#ifndef __WTLGO__NETWORK__HTTP_HEADERS__
#define __WTLGO__NETWORK__HTTP_HEADERS__

#include <memory>

#include <wtlgo/network/Headers.hpp>

namespace wtlgo {
namespace network {
class HttpHeaders : public Headers,
                    public std::enable_shared_from_this<HttpHeaders> {
public:
    using ptr_t = std::shared_ptr<HttpHeaders>;
    using cptr_t = std::shared_ptr<const HttpHeaders>;

    virtual ~HttpHeaders();

    [[nodiscard]] static ptr_t create();

    Headers::ptr_t clone() const override;

    Headers::key_ref_list_t keys() const override;
    Headers::value_ref_opt_t get(Headers::key_ref_t header) const override;
    Headers::ptr_t set(Headers::key_ref_t header, value_ref_t value) override;
    Headers::ptr_t erase(Headers::key_ref_t header) override;

private:
    struct Impl;
    const std::unique_ptr<Impl> impl;

    HttpHeaders();
    HttpHeaders(const std::unique_ptr<Impl>& impl);
};
}
}

#endif
