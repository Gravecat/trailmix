// text/comparison.hpp -- Functions for comparing text to other things.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <string>

namespace trailmix::text::comparison {

std::string find_between(std::string source, std::string before, std::string after);    // Finds a piece of a string between two other strings.
bool    is_number(const std::string& str);  // Checks if a string is a valid number.
bool    is_vowel(char ch);  // Checks if a character is a vowel.
unsigned int    word_count(const std::string& str, const std::string& word);    // Returns a count of the amount of times a string is found in a parent string.

}   // namespace trailmix::text::comparison
