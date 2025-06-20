#include "Wallet.h"
#include "sha256.h"
#include <random>
#include <sstream>
#include <ctime>

// Implementasi Wallet.
// PENTING: Pembuatan kunci ini TIDAK AMAN dan hanya untuk simulasi.
// Kriptografi nyata menggunakan Elliptic Curve Cryptography (ECC).
Wallet::Wallet() {
    // Buat data unik untuk private key simulasi
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000000000);
    _privateKey = std::to_string(distrib(gen)) + std::to_string(time(nullptr));
    
    // Buat public key simulasi dari hash private key
    SHA256 sha;
    sha.update(_privateKey);
    _publicKey = sha.final(); 
}

std::string Wallet::getPublicKey() const {
    return _publicKey;
}

std::string Wallet::getPrivateKey() const {
    return _privateKey;
}
