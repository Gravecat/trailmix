// text/comparison.cpp -- Functions for comparing text to other things.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/text/comparison.hpp"

using std::string;

namespace trailmix::text::comparison {

// Checks if a string is a valid number.
bool is_number(const string &str)
{
    if (!str.size()) return false;
    for (auto ch : str)
        if (!std::isdigit(ch)) return false;
    return true;
}

// Checks if a character is a vowel.
bool is_vowel(char ch)
{
    if (ch >= 'A' && ch <= 'Z') ch += 32;
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}

}   // namespace trailmix::text::comparison
