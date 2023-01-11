#include <random>
#include <algorithm>
#include "utility.hpp"

const std::string test_server = "httpbin.org";

std::string random_string(const std::size_t max_length, const bool exact) {
    static std::mt19937_64 engine{(std::random_device{})()};
    std::uniform_int_distribution<std::size_t> sdist(0, max_length);
    std::uniform_int_distribution<int> cdist(0, 127);

    std::string out;
    std::generate_n(std::back_inserter(out), exact ? max_length : sdist(engine),
                    [&cdist] { return cdist(engine); });
    return out;
}
