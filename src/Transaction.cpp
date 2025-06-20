#include "Transaction.h"
#include "sha256.h"
#include <sstream>
#include <iostream>

std::string Transaction::calculateHash() const {
    std::stringstream ss;
    for (const auto& in : inputs) {
        ss << in.transactionOutputId;
    }
    for (const auto& out : outputs) {
        ss << out.scriptPubKey << out.amount;
    }
    SHA256 sha;
    sha.update(ss.str());
    return sha.final();
}

bool Transaction::isCoinbase() const {
    return inputs.empty();
}

double Transaction::getInputsValue() const {
    double total = 0;
    for (const auto& input : inputs) {
        total += input.UTXO.amount;
    }
    return total;
}

double Transaction::getOutputsValue() const {
    double total = 0;
    for (const auto& output : outputs) {
        total += output.amount;
    }
    return total;
}

// Implementasi simulasi untuk sign dan verify
void Transaction::sign(const std::string& privateKey, const std::map<std::string, TxOutput>& utxos) {
    // Tanda tangan disimulasikan dengan men-hash data + private key
    // Ini TIDAK AMAN dan harus diganti dengan ECDSA
    SHA256 sha;
    sha.update(privateKey + this->calculateHash());
    for(auto& in : inputs) {
        in.signature = sha.final();
    }
}

bool Transaction::verifySignature(const std::map<std::string, TxOutput>& utxos) const {
    // Verifikasi juga disimulasikan. Selalu return true jika ada signature
    // Di dunia nyata, ini adalah proses dekripsi dengan public key
    for(const auto& in : inputs) {
        if(in.signature.empty()) return false;
    }
    return true;
}

