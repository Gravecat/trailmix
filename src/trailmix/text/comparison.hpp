// text/comparison.hpp -- Functions for comparing text to other things.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <string>

namespace trailmix::text::comparison {

bool    is_number(const std::string& str);  // Checks if a string is a valid number.
bool    is_vowel(char ch);  // Checks if a character is a vowel.

}   // namespace trailmix::text::comparison
