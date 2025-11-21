//
// Created by Copilot on 15/11/25.
//

#ifndef KEYDIRENTRY_H
#define KEYDIRENTRY_H

#include <cstdint>
#include <string>

/**
 * KeyDirEntry - Metadata for a key in the Bitcask KeyDir
 * 
 * This structure holds information about where a value is stored on disk:
 * - file_id: Identifier of the data file containing the value
 * - file_path: Path to the data file
 * - value_pos: Byte offset within the file where the value starts
 * - value_size: Size of the value in bytes
 * - timestamp: Unix timestamp when this entry was created/updated
 */
struct KeyDirEntry {
  std::uint64_t file_id{};      // ID of the data file
  std::string file_path;      // Path to the data file
  std::uint64_t value_pos{};    // Byte offset in file where value is stored
  std::uint64_t value_size{};   // Size of the value in bytes
  std::uint64_t timestamp{};    // Unix timestamp

  // Default constructor
  KeyDirEntry() = default;

  // Parameterized constructor
  // - Initialize all member variables with the provided parameters
  // - Use std::move for file_path to avoid unnecessary copying
  KeyDirEntry(std::uint64_t file_id, std::string file_path,
              std::uint64_t value_pos, std::uint64_t value_size,
              std::uint64_t timestamp)
      : file_path(""),
        value_pos(0) {
    this->file_id = file_id;
    this->file_path = file_path;
    this-> value_pos = value_pos;
    this -> value_size = value_size;
    this -> timestamp = timestamp;
  }
};

#endif  // KEYDIRENTRY_H
