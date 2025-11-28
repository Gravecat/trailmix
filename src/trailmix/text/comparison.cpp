// text/comparison.cpp -- Functions for comparing text to other things.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/text/comparison.hpp"

using std::string;

namespace trailmix::text::comparison {

// Finds a piece of a string between two other strings.
string find_between(const std::string& source, const std::string& before, const std::string& after)
{
    const size_t bp = source.find(before, 0);
    if (bp == string::npos) return "";
    const size_t ap = source.find(after, bp);
    if (ap == string::npos) return "";
    return source.substr(bp + before.size(), ap - bp - before.size());
}

// Simple way to check if a string is in another string.
bool instr(const string& input, const string& check) { return (input.find(check, 0) != string::npos); }

// Checks if a string is a valid number.
bool is_number(const string& str)
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
