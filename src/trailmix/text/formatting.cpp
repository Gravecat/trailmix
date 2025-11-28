// text/formatting.cpp -- Utility functions for formatting string in various ways.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/text/formatting.hpp"

using std::string;
using std::vector;

namespace trailmix::text::formatting {

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
