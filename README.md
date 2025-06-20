FreeDomCoin (FDC) - Conceptual Cryptocurrency
Overview
FreeDomCoin (FDC) is a conceptual decentralized peer-to-peer cryptocurrency project being developed from scratch using C++. This project aims to explore the principles and architecture of blockchain technology, focusing on security, transparency, and a limited coin supply.
This project is currently in a conceptual and educational stage. It is NOT a production-ready cryptocurrency and should NOT be used for real financial transactions. The cryptographic implementations are simplified and insecure for real-world use.
Key Features (Conceptual)
 * Blockchain: A growing list of blocks, secured using cryptographic hashing.
 * Transactions: Records of value transfer, utilizing the Unspent Transaction Output (UTXO) model.
 * Mining: A Proof-of-Work (PoW) consensus mechanism where miners create new blocks.
 * Limited Supply: A maximum total supply of 32 million FDC.
 * Difficulty Adjustment: Mining difficulty adjusts to maintain a target block time.
 * Transaction Fees: Miners are incentivized by collecting fees from transactions.
 * Merkle Tree: Implemented for efficient and secure transaction verification within blocks.
 * Simulated Wallets: Basic wallet functionality for generating simulated public and private keys.
 * Basic Transaction Verification: Nodes perform basic checks on transaction validity.
Project Structure
The project is organized into the following directories:
 * build/: Contains the compiled executable and intermediate build files (created during compilation).
 * src/: Holds the source code files (.cpp) for the project.
 * include/: Contains the header files (.h) declaring the classes and functions.
The core source files include:
 * main.cpp: The entry point of the program, demonstrating the basic functionality of the blockchain.
 * sha256.cpp: Implementation of the SHA-256 hashing algorithm.
 * Block.cpp: Implementation of the Block class, representing a block in the blockchain.
 * Blockchain.cpp: Implementation of the Blockchain class, managing the chain, transactions, and mining.
 * Transaction.cpp: Implementation of the Transaction class and its components (inputs and outputs).
 * Wallet.cpp: Implementation of the Wallet class for managing simulated key pairs.
The corresponding header files are located in the include/ directory.
Building and Running
To build and run the project, you will need to have CMake and a C++ compiler (like g++) installed on your system.
 * Navigate to the root directory of the project in your terminal.
 * Create a build directory:
   mkdir build
   cd build
 * Configure the project using CMake:
   cmake ..
 * Compile the source code:
   make
 * Run the executable:
   ./freedomcoin-core
Contributing
This is a personal educational project at this stage. Contributions are not currently being actively sought. However, feedback and suggestions are welcome.
License
This project is currently unlicensed.
Disclaimer
This is a conceptual project and should not be considered a secure or functional cryptocurrency. Use at your own risk.
You can now copy and paste the content of the whitepaper into a .md or .pdf file (or any document format you prefer) and save it. Similarly, create a file named README.md in the root directory of your project and paste the content of the README file into it. When you push your code to GitHub, this README.md file will be automatically displayed on the repository's main page, providing a description of your project.
