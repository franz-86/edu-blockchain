#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include "block.hpp"
#include "transaction.hpp"

/* This is the blockchain class stored in memory by the blockchain node.
 * It contains the full list of blocks, a currentBlock where new transactions are added,
 * and a map tcoin_hash -> tcoin to store all the unspent "coins" (UTXO in the Bitcoin wording). */
class Blockchain
{
public:
    std::vector<Block> blockchain;
    Block currentBlock;                               // current block created after mining the previous one
    std::unordered_map<std::string, TCoin> utcoinMap; // unspent tcoin indexing for fast querying
    int difficulty;
    amount_t miningReward;
    std::string minerAddress;

    Blockchain(int _difficulty, amount_t _miningReward, const std::string &_genesisMsg = "");

    void setMinerAddress(const std::string &address);
    void info();
    bool isUnspent(const TCoin &tcoin);
    void addTransaction(const std::vector<TCoin> &_inputs, const std::string &_spender, const std::string &_recipient, amount_t _amount);
    void mineBlock(const std::string &msg);
};

#endif // BLOCKCHAIN_HPP