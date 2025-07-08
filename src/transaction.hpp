#ifndef TRANSACTION
#define TRANSACTION

/* Transactions in this implementation differs from the actual Bitcoin network.
 * In particular, Bitcoin network makes use of two distinct classes: the Transaction Output (TXO)
 * and the Transaction Input (TXI). They are used to keep the two roles clearly distinct, even
 * if TXIs directly refers to TXOs in a transaction because they are the coins used as
 * input in a new transaction (previously received by the spender as TXOs in previous
 * transactions). This would have led to an higher level of abstraction and increased
 * complexity without adding any value from a pedagogical perspective.
 * In this implementeation, then, i will only use a single class representing the actual
 * money on-chain: the TCoin (Transaction Coin). New TCoins will be created as outputs of
 * a transactions; Old TCoins (yet unspent) will be used as inputs.  */

#include <string>
#include <vector>
#include <cstdint>
#include "types.hpp"

/* The TCoin is the entity actually representing the money on-chain.
 * Coins are like cash or change that can be spent in a future transaction.
 * To keep a parallelism with the Bitcoin blockchain, Coins have the same role
 * of Transaction Outputs.
 * When a block is mined the coinbase transaction generates a new TCoin as the mining reward
 * and assigns it to the miner. */
class TCoin
{
public:
    std::string owner;
    amount_t amount;
    std::string hash;

    TCoin(const std::string &_owner, amount_t _amount);

    void calculateHash(const std::string &txHash, const int index);
    void info() const;
};

/* The Transaction class represents the coin exchange from a spender to a recipient.
 * Some, previously created and not yet spent, Tcoins are used as inputs in the
 * transaction and new TCoins are generated as output: a TCoin is assigned to the
 * recipient with the total amount exchanged; a TCoin is eventually assigned back
 * to the spender as change when the sum of the Tcoin.amoount used as inputs is
 * larger the the amount to be exchanged. */
class Transaction
{
public:
    std::vector<TCoin> inputs;
    std::vector<TCoin> outputs;
    std::int64_t timestamp;
    std::string spender;
    std::string hash;

    Transaction(const std::vector<TCoin> &_inputs, const std::string &_spender, const std::string &_recipient, amount_t _amount);
    void info() const;
};

#endif // TRANSACTION