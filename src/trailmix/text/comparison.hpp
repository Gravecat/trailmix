// text/comparison.hpp -- Functions for comparing text to other things.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <string>

namespace trailmix::text::comparison {

            // Finds a piece of a string between two other strings.
std::string find_between(const std::string& source, const std::string& before, const std::string& after);
bool    instr(const std::string& input, const std::string& check);  // Simple way to check if a string is in another string.
bool    is_number(const std::string& str);  // Checks if a string is a valid number.
bool    is_vowel(char ch);  // Checks if a character is a vowel.
unsigned int    word_count(const std::string& str, const std::string& word);    // Returns a count of the amount of times a string is found in a parent string.

}   // namespace trailmix::text::comparison
