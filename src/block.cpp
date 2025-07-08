#include "block.hpp"
#include "utils/myutils.hpp"
#include <iostream>
#include <sstream>

/* Block constructor */
Block::Block(std::uint64_t _index, const std::string &_previousHash, const std::string &_msg)
    : index(_index), previousHash(_previousHash), msg(_msg) {}

/* Utility/debugging function to print a block info */
void Block::info() const
{
    std::cout << "Block " << index << " with hash: " << hash;
    std::cout << " generated at timestamp: " << timestamp;
    std::cout << " with nonce: " << nonce << std::endl;
    std::cout << "Previous hash: " << previousHash << std::endl;
    std::cout << "Transactions: \n";
    for (const Transaction &tx : txs)
        tx.info();

    std::cout << "\n";
}

/* This utility function serves in the PoW algorithm and counts how many '0's are
 * at the beginning of the hash and compare with the difficulty set on the network. */
bool Block::hashStartsWithZeros(const int difficulty)
{
    if (difficulty > (int)hash.size())
        return false;

    for (int i = 0; i < difficulty; i++)
        if (hash[i] != '0')
            return false;

    return true;
}

/* This implementation differs from Bitcoin blockchain, but keep its fundamental ingredients.
 * This function is called by the blockchain node when the current block has to be mined.
 * The hash is calculated by serializing some info and the transaction hashes. It is
 * mandatory that the previous hash is contained in the string to be hashed in order to create
 * the cryptographic chain at the base of the blockchain security.
 * The PoW algorithm is used, like in the Bitcoin network. */
void Block::calculateHash(const int difficulty)
{
    // for simplicity serialize all tx hash instead of calculating the Merkle root
    std::stringstream ss;
    ss << index << timestamp << previousHash;
    for (const auto &tx : txs)
    {
        ss << tx.hash;
    }

    /* -- Proof of Work algorithm --
     * find a nonce that allows to create a hash that starts with a number of zeros
     * corresponding to the chain difficulty */
    nonce = 0;
    while (true)
    {
        hash = sha256(ss.str() + std::to_string(nonce));
        if (hashStartsWithZeros(difficulty))
            break;

        nonce++;
    }
}

/* Add a transaction to the txs list. All the validation logic is in Blockchain::addTransaction. */
void Block::addTransaction(const Transaction &tx)
{
    txs.push_back(tx);
}