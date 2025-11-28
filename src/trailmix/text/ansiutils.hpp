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

enum class BarType : uint8_t { PROGRESS };

uint32_t    ansii_centre_strvec(std::vector<std::string>& vec); // Centres all the strings in a vector.
std::vector<std::string>    ansi_string_explode(const std::string& str, unsigned int line_len = 80); // String split/explode function, handles ANSI colour tags.
std::string ansi_strip(const std::string& str);     // Strips all ANSI colour tags like {M} from a string.
size_t      ansi_strlen(const std::string& str);    // Returns the length of a specified string, not counting the ANSI colour tags like {G} or {kR}.
std::vector<std::string>    ansi_vector_split(const std::string& str, uint32_t line_length);    // Splits an ANSI-tagged string across multiple lines of text.
size_t      count_colour_tags(const std::string& str);  // Counts all the colour tags in a string.
std::string flatten_tags(const std::string& str);   // 'Flattens' ANSI tags, by erasing redundant tags in the string.
std::string generate_bar(BarType type, float num, float num_max, int width);    // Generates a bar of the specified type.
std::string rainbow_text(const std::string& str, const std::string& colours);   // Makes pretty rainbow text!
                            // Similar to string_explode(), but takes colour tags into account, and wraps to a given line length.
std::vector<std::string>    string_explode_colour(const std::string& str, unsigned int line_len, const std::string& default_colour = "{w}");

}   // namespace trailmix::text::ansi
