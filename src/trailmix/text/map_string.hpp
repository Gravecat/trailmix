// text/map-string.hpp -- Functions to convert an std::map<std::string, std::string> into an std::string, or back into a map.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <map>
#include <string>

namespace trailmix::text::map_string {

std::string map_to_string(const std::map<std::string, std::string>& the_map);   // Converts a map into a string.
void        string_to_map(const std::string& str, std::map<std::string, std::string>& the_map);    // Converts a string to a map.

}   // namespace trailmix::text::map_string
