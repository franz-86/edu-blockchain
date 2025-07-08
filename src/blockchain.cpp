#include "blockchain.hpp"
#include "utils/myutils.hpp"
#include <iostream>

/* Blockchain constructor. */
Blockchain::Blockchain(int _difficulty, amount_t _miningReward, const std::string &_genesisMsg)
    : currentBlock(0, "0"),
      difficulty(_difficulty),
      miningReward(_miningReward)
{
    std::string msg = _genesisMsg.empty() ? "This is the genesis block" : _genesisMsg;
    setMinerAddress("FrancescoAddress");
    mineBlock(msg);
}

/* Setter function to set miner address into this node configuration */
void Blockchain::setMinerAddress(const std::string &address)
{
    minerAddress = address;
}

/* Utility/debugging function that prints all blocks' info */
void Blockchain::info()
{
    for (const auto &block : blockchain)
    {
        block.info();
    }
}

/* Utility function that returns true if a tcoin is still unspent */
bool Blockchain::isUnspent(const TCoin &tcoin)
{
    if (utcoinMap.find(tcoin.hash) != utcoinMap.end())
        return true; // tcoin is in the map
    else
        return false;
}

/* Function that adds a new transaction into the current block. Transaction is here validated */
void Blockchain::addTransaction(const std::vector<TCoin> &inputs, const std::string &spender, const std::string &recipient, amount_t amount)
{
    amount_t total_spent = 0;
    for (const auto &txi : inputs)
    {
        if (txi.owner != spender)
        {
            std::cout << "Error: The spender does not own " << txi.hash << " TCoin\n";
            return;
        }

        if (!isUnspent(txi))
        {
            std::cout << "Error: The TCoin " << txi.hash << " has been already spent\n";
            return;
        }
        total_spent += txi.amount;
    }

    if (total_spent < amount)
    {
        std::cout << "Error: Insufficient funds\n";
        return;
    }

    /* Transaction passed all the validation checks so it can be added to the current block */
    Transaction tx(inputs, spender, recipient, amount);
    currentBlock.addTransaction(tx);

    /* Remove all tcoins spent from utcoinMap */
    for (const auto &tcoin : inputs)
        utcoinMap.erase(utcoinMap.find(tcoin.hash));
}

/* This function is responsible to mine the current block.
 * coinbase transaction with mining reward is added last in the list (in Bitcoin network it is the first) */
void Blockchain::mineBlock(const std::string &msg)
{
    /* Manually adds the coinbase transaction from the blockchain node directly into the currentBlock.
     * As a consequence, it jumps all the validation checks processed in Blockchain::addTransaction.
     * Validation will be held by the other nodes, when this code will implement the p2p network,
     * so remember to consider there the special case spender==COINBASE where no inputs are provided. */
    Transaction coinbase({}, COINBASE, minerAddress, miningReward);
    currentBlock.addTransaction(coinbase);

    /* Complete current block info and starts the mining PoW process */
    currentBlock.msg = msg.empty() ? "" : msg;
    currentBlock.timestamp = getCurrentTimestamp();
    currentBlock.calculateHash(difficulty);

    /* Add all transaction outputs into the unspent tcoin map */
    for (const auto &tx : currentBlock.txs)
        for (const auto &txo : tx.outputs)
            utcoinMap.insert({txo.hash, txo}); // in this way txo is copied for every C++ version (not moved)

    blockchain.push_back(currentBlock);
    std::cout << "New block mined successfully\n";

    /* Construct the new current block */
    currentBlock = Block(blockchain.size(), blockchain.back().hash);
}