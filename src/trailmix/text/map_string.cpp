// text/map-string.cpp -- Functions to convert an std::map<std::string, std::string> into an std::string, or back into a map.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <stdexcept>
#include <vector>

#include "trailmix/text/manipulation.hpp"
#include "trailmix/text/map_string.hpp"

using std::runtime_error;
using std::string;
using std::vector;

namespace trailmix::text::map_string {

// Converts a map into a string.
string map_to_string(const std::map<string, string>& the_map)
{
    string output;
    if (the_map.size())
    {
        for (auto mde : the_map)
            output += mde.first + ":" + mde.second + " ";
        output.pop_back();
    }
    return output;
}

// Converts a string to a map.
void string_to_map(const string& str, std::map<string, string>& the_map)
{
    the_map.clear();
    vector<string> md_exp = manipulation::string_explode(str, " ");
    for (size_t i = 0; i < md_exp.size(); i++)
    {
        vector<string> md_pair = manipulation::string_explode(md_exp.at(i), ":");
        if (md_pair.size() != 2) throw runtime_error("Corrupt map in string conversion.");
        the_map.insert(std::pair<string, string>(md_pair.at(0), md_pair.at(1)));
    }
}

}   // namespace trailmix::text::map_string
