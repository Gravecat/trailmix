// text/conversion.hpp -- Utility functions for doing verious kinds of conversions on strings.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace trailmix::text::conversion {

std::string     bool_to_str(bool b);                    // Converts a bool to a string ("true" or "false").
std::string     collapse_vector(std::vector<std::string> vec);  // Simple function to collapse a string vector into words.
std::string     collapse_vector(std::vector<int> vec);  // As above, but for an integer vector.
std::string     ftos(double num, int precision = 1);    // Converts a float or double to a string.
uint32_t        htoi(const std::string& hex_str);       // Converts a hex string into an integer.
std::string     intostr_pretty(int num);                // Returns a 'pretty' version of a number in string format, such as "12,345".
std::string     intostr_pretty_u64(uint64_t num);       // Unsigned 64-bit version.
std::string     intostr_sign(int num);                  // Converts a nummber (like 5 or -3) to one that always has a sign (e.g. +5 or -3).
std::string     itoh(uint32_t num, uint8_t min_len);    // Converts an integer into a hex string.
std::string     itos(uint32_t num, size_t min_len);     // Converts an integer to a string, but optionally pads it to a minimum length with leading zeroes.
std::string     number_to_text(int64_t num);            // Converts a number (e.g. 123) into a string (e.g. "one hundred and twenty-three").
int32_t         stoi(const std::string& str);           // Converts an integer to a string; handles out-of-range values gracefully.
std::vector<int>    stoi_vec(const std::vector<std::string>& vec);  // Converts a std::string vector into an int vector.
bool            str_to_bool(const std::string& str);    // Converts a string to a bool.
std::wstring    to_wstring(const std::string& str);     // Converts a string to a wstring.

}   // namespace trailmix::text::conversion
