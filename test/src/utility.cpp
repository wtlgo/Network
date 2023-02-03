#include <random>
#include <algorithm>
#include <limits>
#include "utility.hpp"

const std::string test_server = "httpbin.org";

namespace {
std::mt19937_64 engine{(std::random_device{})()};
}

std::string random_string(const std::size_t max_length, const bool exact) {
    std::uniform_int_distribution<std::size_t> sdist{1, max_length};
    std::uniform_int_distribution<int> cdist{std::numeric_limits<char>::min(),
                                             std::numeric_limits<char>::max()};

    std::string out;
    std::generate_n(std::back_inserter(out), exact ? max_length : sdist(engine),
                    [&cdist] { return cdist(engine); });
    return out;
}

unsigned random_unsigned() {
    static std::uniform_int_distribution<unsigned> dist{
        std::numeric_limits<unsigned>::min(),
        std::numeric_limits<unsigned>::max()};
    return dist(engine);
}
