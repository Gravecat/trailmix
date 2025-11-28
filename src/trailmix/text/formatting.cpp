// text/formatting.cpp -- Utility functions for formatting string in various ways.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/text/formatting.hpp"

using std::string;
using std::vector;

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

// Strips trailing newlines from a given string.
string strip_trailing_newlines(string str)
{
    while (!str.empty() && (str.back() == '\n' || str.back() == '\r'))
        str.pop_back();
    return str;
}

}   // namespace trailmix::text::formatting
