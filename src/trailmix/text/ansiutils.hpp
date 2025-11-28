// text/ansiutils.hpp -- Various utility functions that deal with string manipulation/conversion -- in particular, strings that use a special type of tags I use in my own projects
// for marking where ANSI colour codes will be inserted into text.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace trailmix::text::ansi {

std::string ansi_strip(const std::string &str);     // Strips all ANSI colour tags like {M} from a string.
size_t      ansi_strlen(const std::string &str);    // Returns the length of a specified string, not counting the ANSI colour tags like {G} or {kR}.
std::vector<std::string>    ansi_vector_split(const std::string &str, uint32_t line_length);    // Splits an ANSI-tagged string across multiple lines of text.
uint32_t    centre_strvec(std::vector<std::string> &vec);   // Centres all the strings in a vector.
std::string flatten_tags(const std::string &str);   // 'Flattens' ANSI tags, by erasing redundant tags in the string.

}   // namespace trailmix::text::ansi
