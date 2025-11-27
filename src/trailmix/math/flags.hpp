// math/flags.hpp -- Simple functions to perform basic operations on integer flags.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace trailmix {
namespace flags {

bool        flag_check(uint32_t flags, uint32_t flag_to_check); // Checks if a flag is present.
uint32_t    flag_clear(uint32_t flags, uint32_t flag_to_clear); // Clears an integer flag, if it's present.
uint32_t    flag_set(uint32_t flags, uint32_t flag_to_set, bool enable);    // Sets an integer flag directly to on or off.

} } // trailmix, flags namespaces
