// file/fileutils.hpp -- Various utility functions that deal with reading and writing files.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <string>
#include <vector>

namespace trailmix::file::utils {

std::string file_to_string(const std::string& filename);    // Loads a text file into an std::string.
std::vector<std::string>    file_to_vec(const std::string& filename);   // Loads a text file into a vector, one string for each line of the file.

}   // trailmix::file::utils namespace
