# Menentukan versi minimum CMake yang dibutuhkan
cmake_minimum_required(VERSION 3.10)

# Menentukan nama proyek
project(FreeDomCoin)

# Mengatur standar C++ yang akan digunakan (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Menambahkan direktori 'include' agar compiler bisa menemukan file header
include_directories(include)

# Secara otomatis menemukan semua file source (.cpp) di dalam direktori 'src'
aux_source_directory(src DIR_SRCS)

# Membuat file executable bernama 'freedomcoin-core' dari semua file source
add_executable(freedomcoin-core ${DIR_SRCS})
