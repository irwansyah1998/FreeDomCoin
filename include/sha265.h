#ifndef SHA256_H
#define SHA256_H
#include <string>
#include <cstdint>

// Deklarasi kelas untuk algoritma hashing SHA-256
// Implementasi detail ada di sha256.cpp
class SHA256 {
public:
    SHA256();
    void update(const std::string &s);
    void update(const char *data, size_t len);
    std::string final();
};
#endif
