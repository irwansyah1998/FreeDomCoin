#include "Block.h"
#include "sha256.h"
#include <sstream>
#include <iostream>
#include <vector>

// Deklarasi fungsi pembantu Merkle Tree
std::string buildMerkleRoot(std::vector<std::string> hashes);
std::string calculateMerkleRoot(const std::vector<Transaction>& transactions);

// Implementasi fungsi pembantu Merkle Tree
std::string buildMerkleRoot(std::vector<std::string> hashes) {
    if (hashes.empty()) return "";
    if (hashes.size() == 1) return hashes[0];
    if (hashes.size() % 2 != 0) hashes.push_back(hashes.back());

    std::vector<std::string> nextLevelHashes;
    for (size_t i = 0; i < hashes.size(); i += 2) {
        SHA256 sha;
        sha.update(hashes[i] + hashes[i+1]);
        nextLevelHashes.push_back(sha.final());
    }
    return buildMerkleRoot(nextLevelHashes);
}

std::string calculateMerkleRoot(const std::vector<Transaction>& transactions) {
    std::vector<std::string> txHashes;
    for (const auto& tx : transactions) {
        txHashes.push_back(tx.transactionId);
    }
    return buildMerkleRoot(txHashes);
}

// Implementasi kelas Block
Block::Block(uint32_t nIndexIn, const std::vector<Transaction>& transactionsIn)
    : _nIndex(nIndexIn), transactions(transactionsIn), _nNonce(0) {
    tTime = time(nullptr);
    sMerkleRoot = calculateMerkleRoot(this->transactions); 
}

std::string Block::_calculateHash() const {
    std::stringstream ss;
    ss << _nIndex << sPrevHash << tTime << sMerkleRoot << _nNonce;
    SHA256 sha;
    sha.update(ss.str());
    return sha.final();
}

void Block::mineBlock(uint32_t nDifficulty) {
    std::string str(nDifficulty, '0');
    while (_sHash.substr(0, nDifficulty) != str) {
        _nNonce++;
        _sHash = _calculateHash();
    }
    std::cout << "Block mined: " << _sHash << std::endl;
}

bool Block::hasValidTransactions() const {
    if (transactions.empty()) return true;
    if (!transactions[0].isCoinbase()) return false;
    for (size_t i = 1; i < transactions.size(); ++i) {
        if (transactions[i].isCoinbase()) return false;
    }
    // Tambahkan verifikasi signature untuk setiap transaksi di sini
    return true;
}

std::string Block::getHash() const { return _sHash; }
uint32_t Block::getIndex() const { return _nIndex; }
time_t Block::getTime() const { return tTime; }
