// math/misc.cpp -- Miscellaneous utility files for math and number-related tasks.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/misc.hpp"
#include "trailmix/math/random.hpp"

using namespace trailmix::math;

namespace trailmix::math::misc {

// Calculates the distance between two coordinates in 2D space.
float distance_between(const Vector2& start, const Vector2& end)
{
    const float dx = float(start.x - end.x);
    const float dy = float(start.y - end.y);
    return std::sqrt(dx * dx + dy * dy);
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

// Rounds a float to a specified number of digits.
double round_to(double num, unsigned int digits)
{
    if (digits == 2) return ::floorf(num * 100 + 0.5) / 100;    // why does std::floorf() not exist in GCC? :(
    const double power = std::pow(10, digits);
    num *= power;
    const double rounded = std::round(num);
    return rounded / power;
}

}   // namespace trailmix::math::misc
