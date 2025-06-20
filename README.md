
<div align="center">
🪙 FreeDomCoin (FDC)
A Conceptual Peer-to-Peer Cryptocurrency in C++
</div>
<p align="center">
<img alt="Language" src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus">
<img alt="License" src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge">
<img alt="Status"
src="https://img.shields.io/badge/Status-Conceptual-orange?style=for-the-badge">
</p>
💡 Overview
FreeDomCoin (FDC) is a decentralized peer-to-peer cryptocurrency project being developed from scratch using C++. This project serves as an educational tool to explore the core principles and architecture of blockchain technology, with a focus on security, transparency, and a sound monetary policy with a limited coin supply.
> ⚠️ Important Disclaimer
> This project is currently in a conceptual and educational stage. It is NOT a production-ready cryptocurrency and should NOT be used for any real financial transactions. The cryptographic implementations are simplified for learning purposes and are insecure for real-world applications.
> 
🚀 Key Features (Conceptual)
 * Blockchain Core: An immutable, chain-of-blocks ledger secured using SHA-256 cryptographic hashing. *
 * Transaction Model: Utilizes the Unspent Transaction Output (UTXO) model, similar to Bitcoin, for robust value transfer.
 * Consensus Mechanism: Employs a Proof-of-Work (PoW) system where miners compete to create new blocks and secure the network.
 * Limited Supply: A fixed maximum supply of 32 million FDC to create scarcity and a predictable monetary policy.
 * Difficulty Adjustment: A built-in mechanism to dynamically adjust the mining difficulty to maintain a stable target block time.
 * Transaction Fees: Miners are incentivized by collecting transaction fees, calculated as the difference between transaction inputs and outputs.
 * Merkle Tree: Implemented for efficient and secure verification of transactions within each block.
 * Simulated Wallets: Basic functionality for generating and managing simulated public/private key pairs.
 * Transaction Verification: A multi-step verification process to ensure the integrity and validity of every transaction.
🏗️ Project Structure
The project is organized with a clean separation of headers and implementation files.
FreeDomCoin/
├── .gitignore          # Specifies files for Git to ignore
├── CMakeLists.txt      # Build instructions for CMake
├── LICENSE             # The MIT License file
├── README.md           # This file
├── build/              # Directory for compiled files (auto-generated)
├── include/            # Header files (.h)
│   ├── Block.h
│   ├── Blockchain.h
│   ├── Transaction.h
│   ├── Wallet.h
│   └── sha256.h
└── src/                # Source code files (.cpp)
    ├── Block.cpp
    ├── Blockchain.cpp
    ├── Transaction.cpp
    ├── Wallet.cpp
    ├── main.cpp
    └── sha256.cpp

🛠️ Building and Running
To build and run the project, you will need CMake and a C++ compiler (like g++ or Clang) installed on your system.
 * Clone the repository (if it's on GitHub) or ensure you are in the project's root directory.
 * Create and navigate to the build directory:
   mkdir build
cd build

 * Configure the project using CMake:
   This step generates the necessary Makefile or project files.
   cmake ..

 * Compile the source code:
   This step builds the executable file.
   make

 * Run the executable:
   Execute the core program to see the simulation run.
   ./freedomcoin-core

🤝 Contributing
This is primarily a personal educational project. At this stage, contributions are not being actively sought. However, feedback, suggestions, and pointing out potential improvements are always welcome.
📄 License
This project is licensed under the MIT License. See the LICENSE file for more details.
