#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include "myutils.hpp"

/* Wrapper function that computes SHA256 hash using openssl library and returns it as a hex string */
std::string sha256(const std::string &input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(input.c_str()), input.size(), hash);

    std::stringstream ss;
    for (unsigned char byte : hash)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return ss.str();
}