#ifndef BITCASKCONFIG_H
#define BITCASKCONFIG_H

#include <cstdint>
#include <string>

struct BitcaskConfig {
    std::uint64_t max_file_size = 256 * 1024 * 1024;
    bool fsync_each_write = false;
    std::size_t fd_cache_size = 100;
    std::string file_extension = ".data";
    std::string directory = "./data";
};

#endif
