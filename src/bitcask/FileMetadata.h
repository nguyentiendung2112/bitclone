#ifndef FILEMETADATA_H
#define FILEMETADATA_H

#include <cstdint>
#include <string>

struct FileMetadata {
    std::uint64_t file_id;
    std::string file_path;
    int file_descriptor;
    std::uint64_t current_size;
    
    FileMetadata() : file_id(0), file_descriptor(-1), current_size(0) {}
    
    FileMetadata(std::uint64_t id, std::string path, int fd, std::uint64_t size)
        : file_id(id), file_path(std::move(path)), file_descriptor(fd), current_size(size) {}
};

#endif
