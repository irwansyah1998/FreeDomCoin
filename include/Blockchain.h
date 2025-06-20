#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <map>
#include "Block.h"
#include "Transaction.h"
#include "Wallet.h"

class Blockchain {
public:
    Blockchain();

    void minePendingTransactions(const std::string& minerRewardAddress);
    bool addTransaction(Transaction& tx);
    double getBalanceOfAddress(const std::string& address) const;
    bool isChainValid() const;
    Transaction createTransaction(const Wallet& fromWallet, const std::string& toAddress, double amount, double fee);

    std::map<std::string, TxOutput> UTXOs;

private:
    std::vector<Block> _vChain;
    std::vector<Transaction> _pendingTransactions;
    uint32_t _nDifficulty;

    // Aturan Moneter dan Konsensus
    const double INITIAL_BLOCK_REWARD = 152.0;
    const int HALVING_INTERVAL = 105000;
    const int DIFFICULTY_ADJUSTMENT_INTERVAL = 10;
    const time_t TARGET_BLOCK_TIME_SECONDS = 600;

    void _adjustDifficulty();
    double getBlockReward(int chainHeight) const;
    Block _getLastBlock() const;
    bool _verifyTransaction(const Transaction& tx);
};
#endif
