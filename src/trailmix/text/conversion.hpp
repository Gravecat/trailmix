// text/conversion.hpp -- Utility functions for doing verious kinds of conversions on strings.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>

namespace trailmix::text::conversion {

std::string bool_to_str(bool b);    // Converts a bool to a string ("true" or "false").
std::string ftos(double num, int precision = 1);    // Converts a float or double to a string.
std::string number_to_text(int64_t num);    // Converts a number (e.g. 123) into a string (e.g. "one hundred and twenty-three").
std::string str_tolower(std::string str);   // Converts a string to lower-case.

}   // namespace trailmix::text::conversion
