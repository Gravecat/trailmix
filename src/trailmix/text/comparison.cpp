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

// Returns a count of the amount of times a string is found in a parent string.
unsigned int word_count(const string& str, const string& word)
{
    unsigned int count = 0;
    string::size_type word_pos = 0;
    while(word_pos != string::npos)
    {
        word_pos = str.find(word, word_pos);
        if (word_pos != string::npos)
        {
            count++;
            word_pos += word.length();
        }
    }
    return count;
}

}   // namespace trailmix::text::comparison
