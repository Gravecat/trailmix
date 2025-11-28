// math/manipulation.hpp -- Various miscellaneous utility functions that deal with manipulating, changing or transforming numbers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace trailmix::math::manipulation {

double      lerp(double a, double b, double f); // Interpolates between two floating point values.
uint32_t    mixup(unsigned int num, bool big_mix = false);  // Mixes up an integer a little.

}   // namespace trailmix::math::manipulation
