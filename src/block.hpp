#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <cstdint>
#include <vector>
#include "transaction.hpp"

/* The definition of the Block class. */
class Block
{
public:
    std::uint64_t index;
    std::int64_t timestamp;
    std::vector<Transaction> txs;
    std::string previousHash;
    std::string msg;
    std::uint64_t nonce; // used for Proof of Work algorithm to deal with difficulty
    std::string hash;

    Block(std::uint64_t index, const std::string &_previousHash, const std::string &_msg = "");

    void info() const;
    bool hashStartsWithZeros(const int difficulty);
    void calculateHash(const int difficulty);
    void addTransaction(const Transaction &tx);
};

#endif // BLOCK_HPP
