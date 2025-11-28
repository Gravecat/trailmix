// Templates for converting a std::string to a std::set and back again. I can't remember what I used this for originally.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <set>
#include <string>
#include <vector>

#include "trailmix/text/conversion.hpp"
#include "trailmix/text/manipulation.hpp"

namespace trailmix::text::set_string {

template<class T> static std::string set_to_string(std::set<T> the_set)
{
    if (!the_set.size()) return "";
    std::string out_str;
    for (auto num : the_set)
        out_str += conversion::itoh(static_cast<long long>(num), 1) + " ";
    if (out_str.size()) out_str = out_str.substr(0, out_str.size() - 1);    // Strip off the excess space at the end.
    return out_str;
}

template<class T> static void string_to_set(std::string the_string, std::set<T> &the_set)
{
    the_set.clear();
    if (!the_string.size()) return;
    std::vector<std::string> split_string = manipulation::string_explode(the_string, " ");
    for (auto num : split_string)
        the_set.insert(static_cast<T>(conversion::htoi(num)));
}

}   // namespace trailmix::text::set_string
