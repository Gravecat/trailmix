// text/formatting.cpp -- Utility functions for formatting string in various ways.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <cmath>
#include <regex>

#include "trailmix/text/ansiutils.hpp"
#include "trailmix/text/formatting.hpp"

using std::string;
using std::to_string;
using std::vector;
using trailmix::text::ansi::ansi_strlen;

namespace trailmix::text::formatting {

// Capitalizes the first letter of a string.
string capitalize_first_letter(string str)
{
    if (!str.empty()) str[0] = std::toupper(str[0]);
    return str;
}

// Pads a string to be centred to a given width.
string centre_pad(const string& str, unsigned int width)
{
    if (width <= str.size()) return str;
    unsigned int padding = width - str.size();
    return string(padding / 2, ' ') + str + string(padding - (padding / 2), ' ');
}

// Centres all the strings in a vector.
uint32_t centre_strvec(vector<string>& vec)
{
    uint32_t longest = 0;
    for (auto line : vec)
    {
        unsigned int len = line.size();
        if (len > longest) longest = len;
    }
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        int to_add = longest - vec.at(i).size();
        if (!to_add) continue;
        int add_front = to_add / 2;
        int add_back = to_add - add_front;
        vec.at(i) = string(add_front, ' ') + vec.at(i) + string(add_back, ' ');
    }
    return longest;
}

// Converts a vector to a comma-separated list.
string comma_list(vector<string> vec, uint8_t mode)
{
    string plus = ", ";
    if (mode == CL_MODE_USE_AND) plus = " and ";
    else if (mode == CL_MODE_USE_OR) plus = " or ";
    else if (vec.size() == 2) return vec.at(0) + plus + vec.at(1);

    string str;
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        str += vec.at(i);
        if (i < vec.size() - 1)
        {
            if (i == vec.size() - 2) str += plus;
            else str += ", ";
        }
    }
    return str;
}

// Pads a string to a given length.
string pad_string(const string& str, unsigned int min_len, bool ansi)
{
    string output = str;
    uint32_t len = (ansi ? ansi_strlen(str) : str.size());
    if (len < min_len) output += string(min_len - len, ' ');
    return output;
}

// As above, but centers the string.
string pad_string_centre(const string& str, unsigned int min_len, bool ansi)
{
    string output = str;
    uint32_t len = (ansi ? ansi_strlen(str) : str.size());
    if (len < min_len)
    {
        const int padding = min_len - len;
        const int left_padding = std::round(padding / 2.0f);
        const int right_padding = padding - left_padding;
        output = (left_padding ? string(left_padding, ' ') : "") + output + (right_padding ? string(right_padding, ' ') : "");
    }
    return output;
}

// Allows adding conditional tags to a string in the form of [tag_name:conditional text here] and either including or removing the conditional text depending on
// whether the bool is true or false.
void process_conditional_tags(string& str, const string& tag, bool active)
{
    const size_t start = str.find("[" + tag);
    if (start == string::npos) return;
    const size_t end = str.find("]", start);
    if (end == string::npos) return;
    if (active)
    {
        const size_t insert_start = start + tag.size() + 2;
        const string insert = str.substr(insert_start, end - insert_start);
        str = str.substr(0, start) + insert + str.substr(end + 1);
    }
    else str = str.substr(0, start) + str.substr(end + 1);
}

// Right-aligns a percentage string.
string right_align_percentage(uint8_t percent)
{
    string result = to_string(percent) + "%";
    while (result.size() < 4) result = " " + result;
    return result;
}

// Strips all instances of to_remove out of a string.
string strip(string str, char to_remove)
{
    str.erase(std::remove(str.begin(), str.end(), to_remove), str.end());
    return str;
}

// Strips all spaces from within a string.
string strip_spaces(string input)
{
    string::iterator end_pos = std::remove(input.begin(), input.end(), ' ');
    input.erase(end_pos, input.end());
    return input;
}

// Strips trailing newlines from a given string.
string strip_trailing_newlines(string str)
{
    while (!str.empty() && (str.back() == '\n' || str.back() == '\r'))
        str.pop_back();
    return str;
}

// Trims out leading, trailing, and excess (more than one at a time) spaces from a string.
string trim_excess_spaces(const string& source) { return std::regex_replace(source, std::regex("^ +| +$|( ) +"), "$1"); }

}   // namespace trailmix::text::formatting
