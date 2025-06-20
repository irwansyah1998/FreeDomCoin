#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include <map>

// Output dari sebuah transaksi (koin yang belum dibelanjakan)
class TxOutput {
public:
    double amount;
    std::string scriptPubKey; // Alamat publik pemilik

    TxOutput(double amt = 0.0, std::string addr = "") : amount(amt), scriptPubKey(addr) {}
};

// Input untuk sebuah transaksi (referensi ke UTXO sebelumnya)
class TxInput {
public:
    std::string transactionOutputId; // ID dari UTXO yang akan dibelanjakan
    TxOutput UTXO; 
    std::string signature; // Tanda tangan untuk membuktikan kepemilikan

    TxInput(std::string txOutId, TxOutput utxo) : transactionOutputId(txOutId), UTXO(utxo) {}
};

// Kelas utama yang mendefinisikan sebuah transaksi
class Transaction {
public:
    std::string transactionId;
    std::vector<TxInput> inputs;
    std::vector<TxOutput> outputs;

    Transaction() = default; // Konstruktor default

    std::string calculateHash() const;
    bool isCoinbase() const;
    double getInputsValue() const;
    double getOutputsValue() const;
    
    // PENTING: Metode sign dan verify ini disederhanakan untuk simulasi
    void sign(const std::string& privateKey, const std::map<std::string, TxOutput>& utxos);
    bool verifySignature(const std::map<std::string, TxOutput>& utxos) const;
};
#endif
