#include "Blockchain.h"
#include <iostream>
#include <cmath>

Blockchain::Blockchain() {
    _nDifficulty = 4; // Kesulitan awal
    // Genesis block dibuat saat mining pertama kali
}

Block Blockchain::_getLastBlock() const {
    return _vChain.back();
}

double Blockchain::getBlockReward(int chainHeight) const {
    int halvings = floor(chainHeight / HALVING_INTERVAL);
    if (halvings >= 64) return 0;
    return INITIAL_BLOCK_REWARD / pow(2, halvings);
}

void Blockchain::_adjustDifficulty() {
    if (_vChain.size() < DIFFICULTY_ADJUSTMENT_INTERVAL) return;
    if (_vChain.size() % DIFFICULTY_ADJUSTMENT_INTERVAL != 0) return;

    const Block& lastAdjustedBlock = _vChain[_vChain.size() - DIFFICULTY_ADJUSTMENT_INTERVAL];
    const Block& latestBlock = _getLastBlock();
    
    time_t timeExpected = DIFFICULTY_ADJUSTMENT_INTERVAL * TARGET_BLOCK_TIME_SECONDS;
    time_t timeTaken = latestBlock.getTime() - lastAdjustedBlock.getTime();

    if (timeTaken < timeExpected / 2) _nDifficulty++;
    else if (timeTaken > timeExpected * 2 && _nDifficulty > 1) _nDifficulty--;
}

bool Blockchain::_verifyTransaction(const Transaction& tx) {
    if (tx.isCoinbase()) return true;

    // Verifikasi signature simulasi
    if (!tx.verifySignature(this->UTXOs)) return false;

    // Verifikasi nilai
    if (tx.getInputsValue() < tx.getOutputsValue()) return false;

    // Verifikasi bahwa semua input ada di UTXO set
    for (const auto& in : tx.inputs) {
        if (UTXOs.find(in.transactionOutputId) == UTXOs.end()) return false;
    }
    return true;
}

Transaction Blockchain::createTransaction(const Wallet& fromWallet, const std::string& toAddress, double amount, double fee) {
    std::vector<TxInput> inputs;
    double accumulated = 0;
    std::vector<std::pair<std::string, TxOutput>> spendableUTXOs;

    for (const auto& pair : UTXOs) {
        if (pair.second.scriptPubKey == fromWallet.getPublicKey()) {
            spendableUTXOs.push_back(pair);
        }
    }

    for (const auto& pair : spendableUTXOs) {
        accumulated += pair.second.amount;
        inputs.emplace_back(pair.first, pair.second);
        if (accumulated >= amount + fee) break;
    }

    if (accumulated < amount + fee) {
        std::cerr << "Error: Not enough funds. Required: " << amount + fee << ", Available: " << accumulated << std::endl;
        return Transaction(); // Return transaksi kosong/invalid
    }

    Transaction newTx;
    newTx.inputs = inputs;
    newTx.outputs.emplace_back(amount, toAddress);
    double change = accumulated - amount - fee;
    if (change > 0) {
        newTx.outputs.emplace_back(change, fromWallet.getPublicKey());
    }

    newTx.transactionId = newTx.calculateHash();
    newTx.sign(fromWallet.getPrivateKey(), this->UTXOs);

    return newTx;
}


bool Blockchain::addTransaction(Transaction& tx) {
    if (tx.transactionId.empty()) return false; // Transaksi invalid dari createTransaction
    if (!_verifyTransaction(tx)) {
        std::cerr << "Transaction verification failed. Discarding." << std::endl;
        return false;
    }
    _pendingTransactions.push_back(tx);
    return true;
}

void Blockchain::minePendingTransactions(const std::string& minerRewardAddress) {
    double totalFees = 0;
    for (const auto& tx : _pendingTransactions) {
        totalFees += (tx.getInputsValue() - tx.getOutputsValue());
    }

    Transaction rewardTx;
    rewardTx.outputs.emplace_back(getBlockReward(_vChain.size()) + totalFees, minerRewardAddress);
    rewardTx.transactionId = rewardTx.calculateHash();

    std::vector<Transaction> blockTransactions;
    blockTransactions.push_back(rewardTx);
    blockTransactions.insert(blockTransactions.end(), _pendingTransactions.begin(), _pendingTransactions.end());

    uint32_t newIndex = _vChain.size();
    Block newBlock(newIndex, blockTransactions);
    if (newIndex > 0) newBlock.sPrevHash = _getLastBlock().getHash();
    
    newBlock.mineBlock(_nDifficulty);
    _vChain.push_back(newBlock);

    // Update UTXO Set
    for (const auto& tx : newBlock.transactions) {
        if (!tx.isCoinbase()) {
            for (const auto& input : tx.inputs) {
                UTXOs.erase(input.transactionOutputId);
            }
        }
        for (size_t i = 0; i < tx.outputs.size(); ++i) {
            std::string txOutputId = tx.transactionId + std::to_string(i);
            UTXOs[txOutputId] = tx.outputs[i];
        }
    }

    _pendingTransactions.clear();
    _adjustDifficulty();
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < _vChain.size(); i++) {
        const Block& currentBlock = _vChain[i];
        const Block& previousBlock = _vChain[i - 1];

        if (currentBlock.getHash() != currentBlock._calculateHash()) return false;
        if (currentBlock.sPrevHash != previousBlock.getHash()) return false;
        if (!currentBlock.hasValidTransactions()) return false;
    }
    return true;
}

double Blockchain::getBalanceOfAddress(const std::string& address) const {
    double total = 0;
    for (const auto& item : UTXOs) {
        if (item.second.scriptPubKey == address) {
            total += item.second.amount;
        }
    }
    return total;
}
