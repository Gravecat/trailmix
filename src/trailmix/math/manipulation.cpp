// math/manipulation.cpp -- Various miscellaneous utility functions that deal with manipulating, changing or transforming numbers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/math/manipulation.hpp"
#include "trailmix/math/random.hpp"

namespace trailmix::math::manipulation {

// Interpolates between two floating point values.
double lerp(double a, double b, double f) { return (a * (1.0f - f)) + (b * f); }

// Mixes up an integer a little.
uint32_t mixup(unsigned int num, bool big_mix)
{
    int64_t variance = num / (big_mix ? 2 : 10);
    if (variance <= 0) variance = 1;
    uint32_t result = static_cast<uint32_t>(num) + random::get<int>(0, variance * 2) - variance;
    if (result < 1) result = 1;
    return result;
}

}   // namespace trailmix::math::manipulation
