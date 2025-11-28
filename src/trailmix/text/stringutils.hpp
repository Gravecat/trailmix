// text/stringutils.hpp -- Various utility functions that deal with string manipulation/conversion.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace trailmix::text::utils {

std::string decode_compressed_string(std::string cb);   // Decodes a compressed string (e.g. 4cab2z becomes ccccabzz).
bool        find_and_replace(std::string &input, const std::string &to_find, const std::string &to_replace);    // Find and replace one string with another.
std::vector<std::string>    string_explode(std::string str, const std::string& separator = " ");    // String split/explode function.

}   // namespace trailmix::text::utils
