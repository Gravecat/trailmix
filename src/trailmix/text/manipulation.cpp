// text/manipulation.cpp -- Various miscellaneous utility functions that deal with string manipulation.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <numeric>

#include "trailmix/text/conversion.hpp"
#include "trailmix/text/manipulation.hpp"

using namespace trailmix::text::conversion;
using std::string;
using std::transform;
using std::vector;

namespace trailmix::text::manipulation {

// Decodes a compressed string (e.g. 4cab2z becomes ccccabzz).
string decode_compressed_string(string cb)
{
    string result;
    while(cb.size())
    {
        string letter = cb.substr(0, 1);
        cb = cb.substr(1);
        if (letter[0] >= '0' && letter[0] <= '9')
        {
            int number = letter[0] - '0';
            letter = cb.substr(0, 1);
            cb = cb.substr(1);
            while (letter[0] >= '0' && letter[0] <= '9')
            {
                number *= 10;
                number += letter[0] - '0';
                letter = cb.substr(0, 1);
                cb = cb.substr(1);
            }
            result += string(number, letter[0]);
        }
        else result += letter;
    }
    return result;
}

// Find and replace one string with another.
bool find_and_replace(string& input, const string& to_find, const string& to_replace)
{
    string::size_type pos = 0;
    const string::size_type find_len = to_find.length(), replace_len = to_replace.length();
    if (find_len == 0) return false;
    bool found = false;
    while ((pos = input.find(to_find, pos)) != string::npos)
    {
        found = true;
        input.replace(pos, find_len, to_replace);
        pos += replace_len;
    }
    return found;
}

// Takes a vector of strings and squashes them into one string.
string join_words(vector<string> vec, const string& spacer)
{ return std::accumulate(vec.begin() + 1, vec.end(), vec[0], [&spacer](const std::string& a, const std::string& b) { return a + spacer + b; }); }

// Makes a string into a possessive noun (e.g. orc = orc's, platypus = platypus')
string possessive_string(const string& str)
{
    if (str.empty()) return "";
    if (str[str.size() - 1] == 's' || str[str.size() - 1] == 'S') return str + "'";
    else return str + "'s";
}

// Replaces input with output, maintaining the capitalization of input (e.g. input="Meow" output="cat" result="Cat")
string replace_keep_capitalization(const string& input, const string& output)
{
    if (!input.size() || !output.size()) return "";
    string result = str_tolower(output);

    bool first_letter_caps = (input[0] >= 'A' && input[0] <= 'Z');
    bool all_caps = (input.size() > 2 && input[1] >= 'A' && input[1] <= 'Z');

    if (all_caps) return str_toupper(result);
    else if (first_letter_caps && result[0] >= 'a' && result[0] <= 'z') result[0] -= 32;

    return result;
}

// Converts a string to lower-case.
string str_tolower(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Converts a string to upper-case.
string str_toupper(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// String split/explode function.
vector<string> string_explode(string str, const string& separator)
{
    vector<string> results;

    string::size_type pos = str.find(separator, 0);
    const size_t pit = separator.length();

    while(pos != string::npos)
    {
        if (pos == 0) results.push_back("");
        else results.push_back(str.substr(0, pos));
        str.erase(0, pos + pit);
        pos = str.find(separator, 0);
    }
    results.push_back(str);

    return results;
}

}   // namespace trailmix::text::manipulation
