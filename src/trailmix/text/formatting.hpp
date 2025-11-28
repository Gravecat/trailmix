// text/formatting.hpp -- Utility functions for formatting string in various ways.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace trailmix::text::formatting {

static constexpr uint8_t CL_MODE_USE_AND = 1;   // Use 'and' for the last entry in comma_list().
static constexpr uint8_t CL_MODE_USE_OR =  2;   // Use 'or' for the last entry in comma_list();

std::string capitalize_first_letter(std::string str);   // Capitalizes the first letter of a string.
std::string centre_pad(const std::string& str, unsigned int width); // Pads a string to be centred to a given width.
uint32_t    centre_strvec(std::vector<std::string>& vec);   // Centres all the strings in a vector.
std::string comma_list(std::vector<std::string> vec, uint8_t mode = 0);    // Converts a vector to a comma-separated list.
std::string pad_string(const std::string& str, unsigned int min_len, bool ansi = false);    // Pads a string to a given length.
std::string pad_string_centre(const std::string& str, unsigned int min_len, bool ansi = false); // As above, but centres the string.
std::string strip(std::string str, char to_remove); // Strips all instances of to_remove out of a string.
std::string strip_trailing_newlines(std::string str);   // Strips trailing newlines from a given string.

}   // namespace trailmix::text::formatting
