#include "transaction.hpp"
#include "utils/myutils.hpp"
#include <sstream>
#include <iostream>

/* The TCoin constructor.
 * The hash calculation will be performed only when a new transaction is added into a block */
TCoin::TCoin(const std::string &_owner, amount_t _amount) : owner(_owner), amount(_amount) {}

void TCoin::calculateHash(const std::string &txHash, const int index)
{
    hash = sha256(txHash + std::to_string(index));
}

void TCoin::info() const
{
    std::cout << hash << ": " << amount / COIN << " - " << owner << std::endl;
}

/* The Transaction constructor initialize timestamp, spender, and txi, txo lists.
 * Then it calculate the transaction hash.
 * The constructor assumes that the Transaction is valid:
 * validation logic is managed in the Block::addTransaction method.
 * Only when transaction hash is calculated, this function will calculate and store the
 * hash of all the outputs */
Transaction::Transaction(
    const std::vector<TCoin> &_inputs,
    const std::string &_spender,
    const std::string &_recipient,
    amount_t _amount)
    : timestamp(getCurrentTimestamp()),
      spender(_spender)
{
    amount_t total_spent = 0;
    for (const auto &txi : _inputs)
    {
        inputs.push_back(txi);
        total_spent += txi.amount;
    }

    /* create the two outputs: one for the recipient and one, eventually, for the spender as change.
     * For deterministic serialization purposes (see later) it is important to always keep the same order. */
    outputs.emplace_back(_recipient, _amount);
    if (total_spent > _amount)
        outputs.emplace_back(_spender, total_spent - _amount);

    /* Calculate transaction hash by serializing all tx inputs and outputs.
     * Note that it is important to keep timestamp in the string to be hashed because it
     * produces different hashes even if we have two coinbase transaction to the same miner address. */
    std::stringstream ss;
    ss << _spender << timestamp;

    for (const auto &txi : inputs)
    {
        ss << txi.hash; // inputs already have an hash since they have been created in previous transactions
    }
    /* the serialization of all transaction outputs is performed here */
    for (const auto &txo : outputs)
    {
        ss << txo.owner << txo.amount;
    }
    hash = sha256(ss.str());

    /* Now calculate the hash of all the transaction outputs */
    int i = 0; // txo index
    /* transaction output index is required to differentiate the two tcoins produced in the transaction,
     * otherwise both txos would have the same hash */
    for (auto &txo : outputs)
    {
        txo.calculateHash(hash, i);
        i++;
    }
}

void Transaction::info() const
{
    std::cout << "  - hash: " << hash << std::endl;
    for (const auto &txi : inputs)
    {
        std::cout << "  - input ";
        txi.info();
    }

    for (const auto &txo : outputs)
    {
        std::cout << "  - output ";
        txo.info();
    }
}