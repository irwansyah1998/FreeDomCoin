#ifndef WALLET_H
#define WALLET_H
#include <string>

// Kelas untuk merepresentasikan dompet pengguna
// Mensimulasikan kepemilikan kunci privat dan publik
class Wallet {
public:
    Wallet();
    std::string getPublicKey() const;
    std::string getPrivateKey() const; // Hanya untuk keperluan simulasi

private:
    std::string _privateKey;
    std::string _publicKey;
};
#endif
