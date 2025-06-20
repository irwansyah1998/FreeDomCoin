#ifndef BLOCK_H
#define BLOCK_H
#include <cstdint>
#include <vector>
#include <string>
#include "Transaction.h"

class Block {
public:
    std::string sPrevHash;
    std::string sMerkleRoot;
    std::vector<Transaction> transactions;
    time_t tTime;
    
    Block(uint32_t nIndexIn, const std::vector<Transaction>& transactionsIn);
    
    std::string getHash() const;
    void mineBlock(uint32_t nDifficulty);
    bool hasValidTransactions() const;
    
    // Getter untuk atribut privat
    uint32_t getIndex() const;
    time_t getTime() const;

private:
    uint32_t _nIndex;
    int64_t _nNonce;
    std::string _sHash;
    
    std::string _calculateHash() const;
};
#endif
