// math/manipulation.hpp -- Various miscellaneous utility functions that deal with manipulating, changing or transforming numbers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace trailmix::math::manipulation {

uint32_t        fuzz(uint32_t num); // Fuzzes a number, giving an estimate (e.g. 123456 becoomes 100000).
double          lerp(double a, double b, double f); // Interpolates between two floating point values.
uint32_t        mixup(unsigned int num, bool big_mix = false);  // Mixes up an integer a little.
unsigned char   sneaky_xor(unsigned char src, unsigned char mask);  // It's like XOR, but sneakier.

}   // namespace trailmix::math::manipulation
