// file/fileutils.hpp -- Various utility functions that deal with reading and writing files.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace trailmix::file::utils {

uint32_t        crc32c(uint32_t crc, const unsigned char* buf, size_t len); // Simple CRC32 implementation.
unsigned int    count_lines(const std::string& file);   // Counts the number of lines in a file.
std::string     file_to_string(const std::string& filename);    // Loads a text file into an std::string.
std::vector<std::string>    file_to_vec(const std::string& filename);   // Loads a text file into a vector, one string for each line of the file.
std::vector<std::string>    files_in_dir(const std::filesystem::path& directory, bool recursive = false);   // Returns a list of files in a given directory.

}   // trailmix::file::utils namespace
