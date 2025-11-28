// text/stringutils.hpp -- Various utility functions that deal with string manipulation/conversion.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace trailmix::text::utils {

static constexpr uint8_t CL_MODE_USE_AND = 1;   // Use 'and' for the last entry in comma_list().
static constexpr uint8_t CL_MODE_USE_OR =  2;   // Use 'or' for the last entry in comma_list();

std::string comma_list(std::vector<std::string> vec, uint8_t mode = 0);    // Converts a vector to a comma-separated list.
std::string decode_compressed_string(std::string cb);   // Decodes a compressed string (e.g. 4cab2z becomes ccccabzz).
bool        find_and_replace(std::string &input, const std::string &to_find, const std::string &to_replace);    // Find and replace one string with another.
std::string number_to_text(int64_t num);    // Converts a number (e.g. 123) into a string (e.g. "one hundred and twenty-three").
std::string str_tolower(std::string str);   // Converts a string to lower-case.
std::vector<std::string>    string_explode(std::string str, const std::string& separator = " ");    // String split/explode function.
std::string strip_trailing_newlines(std::string str);   // Strips trailing newlines from a given string.

}   // namespace trailmix::text::utils
