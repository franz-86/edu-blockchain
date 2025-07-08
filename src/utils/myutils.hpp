#ifndef MYUTILS_HPP
#define MYUTILS_HPP

/* Definitions of several utility functions */

#include <string>

std::string sha256(const std::string &input);

std::int64_t getCurrentTimestamp();

#endif // MYUTILS_HPP