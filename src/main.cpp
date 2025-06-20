#include <iostream>
#include "Blockchain.h"
#include "Wallet.h"
#include "Transaction.h"

// Kode main.cpp dari sesi pengujian sebelumnya bisa digunakan di sini.
// Pastikan untuk menyesuaikan jika ada perubahan nama fungsi atau logika.
int main() {
    std::cout << "===== Memulai Simulasi Uji Coba FreeDomCoin (FDC) v0.3 =====\n" << std::endl;

    // 1. Inisialisasi
    Blockchain fdcChain;
    Wallet minerWallet, aliceWallet, bobWallet;
    std::cout << "[INFO] Blockchain dan Wallet berhasil dibuat." << std::endl;
    std::cout << "       - Alamat Miner: " << minerWallet.getPublicKey().substr(0, 15) << "..." << std::endl;
    std::cout << "       - Alamat Alice: " << aliceWallet.getPublicKey().substr(0, 15) << "..." << std::endl;
    std::cout << "       - Alamat Bob:   " << bobWallet.getPublicKey().substr(0, 15) << "...\n" << std::endl;

    // 2. Menambang Genesis Block
    std::cout << "[AKSI] Miner menambang Genesis Block..." << std::endl;
    fdcChain.minePendingTransactions(minerWallet.getPublicKey());
    std::cout << "[HASIL] Saldo Miner: " << fdcChain.getBalanceOfAddress(minerWallet.getPublicKey()) << " FDC\n" << std::endl;
    
    // 3. Uji Transaksi VALID (Miner ke Alice) dengan Biaya Transaksi
    std::cout << "[AKSI] Miner mengirim 50 FDC ke Alice, dengan fee 0.5 FDC." << std::endl;
    Transaction tx1 = fdcChain.createTransaction(minerWallet, aliceWallet.getPublicKey(), 50.0, 0.5);
    if(fdcChain.addTransaction(tx1)) 
        std::cout << "       -> Transaksi berhasil ditambahkan ke pending pool.\n" << std::endl;

    std::cout << "[AKSI] Miner menambang blok baru..." << std::endl;
    fdcChain.minePendingTransactions(minerWallet.getPublicKey());
    std::cout << "[HASIL] Saldo Alice: " << fdcChain.getBalanceOfAddress(aliceWallet.getPublicKey()) << " FDC" << std::endl;
    std::cout << "[HASIL] Saldo Miner: " << fdcChain.getBalanceOfAddress(minerWallet.getPublicKey()) << " FDC\n" << std::endl;

    // 4. Uji Transaksi TIDAK VALID (Alice mencoba over-spend)
    std::cout << "[AKSI] Alice mencoba mengirim 60 FDC (saldo hanya 50) ke Bob." << std::endl;
    Transaction tx2_invalid = fdcChain.createTransaction(aliceWallet, bobWallet.getPublicKey(), 60.0, 0.1);
    if(!fdcChain.addTransaction(tx2_invalid)) 
        std::cout << "       -> Transaksi DITOLAK oleh sistem (sesuai harapan).\n" << std::endl;
    
    // 5. Uji Transaksi VALID kedua (Alice ke Bob)
    std::cout << "[AKSI] Alice mengirim 15 FDC ke Bob dengan fee 0.2 FDC." << std::endl;
    Transaction tx3_valid = fdcChain.createTransaction(aliceWallet, bobWallet.getPublicKey(), 15.0, 0.2);
    if(fdcChain.addTransaction(tx3_valid))
        std::cout << "       -> Transaksi berhasil ditambahkan ke pending pool.\n" << std::endl;

    std::cout << "[AKSI] Miner menambang blok terakhir..." << std::endl;
    fdcChain.minePendingTransactions(minerWallet.getPublicKey());
    std::cout << "[HASIL] Saldo Bob: " << fdcChain.getBalanceOfAddress(bobWallet.getPublicKey()) << " FDC" << std::endl;
    std::cout << "[HASIL] Saldo Alice: " << fdcChain.getBalanceOfAddress(aliceWallet.getPublicKey()) << " FDC" << std::endl;
    std::cout << "[HASIL] Saldo Miner: " << fdcChain.getBalanceOfAddress(minerWallet.getPublicKey()) << " FDC\n" << std::endl;

    // 6. Validasi Final
    std::cout << "===== Uji Coba Selesai. Melakukan Validasi Final... =====\n" << std::endl;
    if(fdcChain.isChainValid())
        std::cout << "[FINAL] Apakah seluruh rantai blockchain valid? YA" << std::endl;
    else
        std::cout << "[FINAL] Apakah seluruh rantai blockchain valid? TIDAK" << std::endl;

    return 0;
}

