// math/manipulation.cpp -- Various miscellaneous utility functions that deal with manipulating, changing or transforming numbers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/manipulation.hpp"
#include "trailmix/math/random.hpp"

namespace trailmix::math::manipulation {

// Fuzzes a number, giving an estimate (e.g. 123456 becoomes 100000).
uint32_t fuzz(uint32_t num)
{
    if (num >= 1000000000) { num = std::round(num / 100000000.0f); return num * 100000000; }
    if (num >= 100000000) { num = std::round(num / 10000000.0f); return num * 10000000; }
    if (num >= 10000000) { num = std::round(num / 1000000.0f); return num * 1000000; }
    if (num >= 1000000) { num = std::round(num / 100000.0f); return num * 100000; }
    if (num >= 100000) { num = std::round(num / 10000.0f); return num * 10000; }
    if (num >= 10000) { num = std::round(num / 1000.0f); return num * 1000; }
    if (num >= 1000) { num = std::round(num / 100.0f); return num * 100; }
    if (num >= 50) { num = std::round(num / 10.0f); return num * 10; }
    if (num >= 25) return num + static_cast<uint32_t>(std::abs((static_cast<int32_t>(num) % 5) - 5));
    return num;
}

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

// It's like XOR, but sneakier.
unsigned char sneaky_xor(unsigned char src, unsigned char mask)
{
    if (src == mask || (src ^ mask) == ' ' || (src ^ mask) == '\n' || (src ^ mask) == 1) return src;
    else if (src == ' ') return 0;
    else if (src == 0) return ' ';
    else if (src == '\n') return 1;
    else if (src == 1) return '\n';
    else return src ^ mask;
}

}   // namespace trailmix::math::manipulation
