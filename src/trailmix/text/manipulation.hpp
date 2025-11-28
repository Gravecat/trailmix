// text/manipulation.hpp -- Various miscellaneous utility functions that deal with string manipulation.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace trailmix::text::manipulation {

std::string decode_compressed_string(std::string cb);   // Decodes a compressed string (e.g. 4cab2z becomes ccccabzz).
bool        find_and_replace(std::string& input, const std::string& to_find, const std::string& to_replace);    // Find and replace one string with another.
std::string join_words(std::vector<std::string> vec, const std::string& spacer = " ");  // Takes a vector of strings and squashes them into one string.
std::string possessive_string(const std::string& str);  // Makes a string into a possessive noun (e.g. orc = orc's, platypus = platypus')
std::string str_tolower(std::string str);   // Converts a string to lower-case.
std::vector<std::string>    string_explode(std::string str, const std::string& separator = " ");    // String split/explode function.

}   // namespace trailmix::text::manipulation
