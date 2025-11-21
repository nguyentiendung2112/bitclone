#ifndef STORESTATS_H
#define STORESTATS_H

#include <cstddef>
#include <cstdint>

struct StoreStats {
    std::size_t total_keys;
    std::size_t total_files;
    std::uint64_t total_size;
    std::uint64_t active_file_size;
    
    StoreStats() : total_keys(0), total_files(0), total_size(0), active_file_size(0) {}
};

#endif
