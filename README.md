# Edu-Blockchain

This project is my attempt at implementing a **toy blockchain** from scratch in C++.  
The primary aim is **educational** — to keep the implementation clean, readable, and focused on the core concepts of a blockchain.

I concentrate on fundamental features such as:

- The hash-linked chain of blocks
- Transactions as structured data
- The mechanics of transaction outputs (UTXO-style)

This project is clearly inspired by the Bitcoin protocol, but it is **not a replica**, for two main reasons:

1. There’s no need to clone Bitcoin.
2. A full replica would be too complex and full of technical details, which would defeat the educational purpose.  
   Instead, I prioritize simplicity — even when it leads to technical solutions that differ from Bitcoin (e.g., the custom `TCoin` class for transaction outputs).

---

## Implementation Notes

The code is written in **modern C++**, leveraging STL containers like `std::vector` and `std::unordered_map`.  
Some common OOP principles have been intentionally relaxed to improve clarity:

- Attributes are kept `public` to avoid bloating the code with accessors.
- Code is kept flat and focused on functionality over encapsulation.

The goal is to reduce boilerplate and keep the reader focused on **how blockchains work**, not on writing "perfect C++."

---

## Current Limitations

This is still a work-in-progress and far from what a production blockchain would require.

- No networking yet
- No peer discovery or node consensus
- No persistent storage
- No cryptographic signatures yet (but coming soon)

---

## Planned Features

1. Wallet client (keypair, UTXO management, signing)
2. Wallet-to-node interaction (transaction broadcast, balance query)
3. Peer-to-peer node communication and block propagation
4. Node-side transaction validation and basic consensus

---

## How to Compile

This project includes a `Makefile` for building the code with `g++`.

### Requirements

- A C++17-compatible compiler (e.g., `g++`)
- OpenSSL (used for SHA-256 hashing)

### Build

To compile the project, run:

```sh
make
```

### Run

To run the code, run:

```sh
./edublockchain
```

### Clean

To remove the compiled binary, run:

```sh
make clean
```

**Note**: OpenSSL is the only external dependency. Make sure its headers and libraries are properly linked if you're not using macOS like me.

---

MIT License — free to use, study, modify, and learn from.
