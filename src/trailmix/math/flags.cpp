// math/flags.cpp -- Simple functions to perform basic operations on integer flags.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/math/flags.hpp"

namespace trailmix::math::flags {

// Checks if a flag is present.
bool flag_check(uint32_t flags, uint32_t flag_to_check) { return (flags & flag_to_check) == flag_to_check; }

// Clears an integer flag, if it's present.
uint32_t flag_clear(uint32_t flags, uint32_t flag_to_clear)
{
    if (flag_check(flags, flag_to_clear)) return flags ^ flag_to_clear;
    else return flags;
}

// Sets an integer flag directly to on or off.
uint32_t flag_set(uint32_t flags, uint32_t flag_to_set, bool enable)
{
    if (enable) return flags | flag_to_set;
    else return flag_clear(flags, flag_to_set);
}

}   // trailmix::math::flags namespace
