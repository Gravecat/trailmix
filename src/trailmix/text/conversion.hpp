// text/conversion.hpp -- Utility functions for doing verious kinds of conversions on strings.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>

namespace trailmix::text::conversion {

std::string     bool_to_str(bool b);                    // Converts a bool to a string ("true" or "false").
std::string     ftos(double num, int precision = 1);    // Converts a float or double to a string.
uint32_t        htoi(const std::string& hex_str);       // Converts a hex string into an integer.
std::string     intostr_pretty(int num);                // Returns a 'pretty' version of a number in string format, such as "12,345".
std::string     intostr_pretty_u64(uint64_t num);       // Unsigned 64-bit version.
std::string     intostr_sign(int num);                  // Converts a nummber (like 5 or -3) to one that always has a sign (e.g. +5 or -3).
std::string     itoh(uint32_t num, uint8_t min_len);    // Converts an integer into a hex string.
std::string     number_to_text(int64_t num);            // Converts a number (e.g. 123) into a string (e.g. "one hundred and twenty-three").
bool            str_to_bool(const std::string& str);    // Converts a string to a bool.
std::wstring    to_wstring(const std::string& str);     // Converts a string to a wstring.

}   // namespace trailmix::text::conversion
