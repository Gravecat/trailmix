// file/fileutils.cpp -- Various utility functions that deal with reading and writing files.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <filesystem>
#include <fstream>
#include <sstream>

#include "trailmix/file/fileutils.hpp"

using std::runtime_error;
using std::string;
using std::vector;
namespace fs = std::filesystem;

namespace trailmix::file::utils {

// Counts the number of lines in a file.
unsigned int count_lines(const string& file)
{
    std::ifstream fh(file);
    unsigned int count = 0;
    string line;
    while (std::getline(fh, line)) count++;
    fh.close();
    return count;
}

// Simple CRC32 implementation.
uint32_t crc32c(uint32_t crc, const unsigned char* buf, size_t len)
{
    crc = ~crc;
    while(len--)
    {
        crc ^= *buf++;
        for (int k = 0; k < 8; k++)
            crc = crc & 1 ? (crc >> 1) ^ 0x82f63b78 : crc >> 1;
    }
    return ~crc;
}

// Loads a text file into an std::string.
string file_to_string(const string& filename)
{
    if (!fs::exists(filename)) throw runtime_error("Invalid file: " + filename);
    std::ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Cannot open file: " + filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

// Loads a text file into a vector, one string for each line of the file.
vector<string> file_to_vec(const string& filename)
{
    if (!fs::exists(filename)) throw runtime_error("Invalid file: " + filename);
    vector<string> lines;
    std::ifstream file(filename);
    if (!file.is_open()) throw runtime_error("Cannot open file: " + filename);

    string line;
    while (std::getline(file, line))
    {
        if (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
        lines.push_back(line);
    }
    file.close();
    return lines;
}

} // trailmix::file::utils namespace
