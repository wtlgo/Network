#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_

#include <string>

extern const std::string test_server;

std::string random_string(size_t max_length = 100, bool exact = false);
unsigned random_unsigned();

#endif
