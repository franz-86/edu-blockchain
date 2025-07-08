#include "blockchain.hpp"
#include "types.hpp"
#include <iostream>

/* Just testing the implemented functionalities. */
int main()
{
    /* Construct the blockchain with difficulty set to 5, 16COIN as mining rewards and a genesis msg. */
    Blockchain mychain(5, 16 * COIN, "my genesis");
    /* In this second block a new transaction is added, moving some coin to Alice.
     * I'm also testing an invalid transaction: I should read an error message in the terminal. */
    mychain.addTransaction(mychain.blockchain.back().txs[0].outputs, "FrancescoAddress", "AliceAddress", 2 * COIN);
    mychain.addTransaction(mychain.blockchain.back().txs[0].outputs, "BobAddress", "AliceAddress", 10 * COIN);
    mychain.mineBlock("second block");

    /* Print blockchain info to debug hashes */
    mychain.info();

    /* Print all utxos and balances to check if transactions worked properly. */
    std::cout << " -------- Print all utxos: -------- \n";
    amount_t myTotal = 0, aliceTotal = 0;
    for (const auto &utxo : mychain.utcoinMap)
    {
        utxo.second.info();
        if (utxo.second.owner == "FrancescoAddress")
            myTotal += utxo.second.amount;
        if (utxo.second.owner == "AliceAddress")
            aliceTotal += utxo.second.amount;
    }
    std::cout << "FrancescoAddress owns " << myTotal / COIN << " coins\n";
    std::cout << "AliceAddress owns " << aliceTotal / COIN << " coins\n";
    return 0;
}