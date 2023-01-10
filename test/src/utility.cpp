#include <random>
#include <algorithm>
#include "utility.hpp"

const std::string test_server = "httpbin.org";

std::string random_string(size_t max_length) {
    static std::mt19937_64 engine{(std::random_device())()};
    std::uniform_int_distribution<size_t> sdist(0, max_length);
    std::uniform_int_distribution<char> cdist(0, 127);

    std::string out;
    std::generate_n(std::back_inserter(out), sdist(engine),
                    [&cdist] { return cdist(engine); });
    return out;
}
