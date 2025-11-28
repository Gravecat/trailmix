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

}   // namespace trailmix::text::comparison
