// math/misc.cpp -- Miscellaneous utility files for math and number-related tasks.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>
#include <stdexcept>
#include <string>

#include "trailmix/math/misc.hpp"
#include "trailmix/math/random.hpp"

using namespace trailmix::math;
using std::runtime_error;
using std::to_string;

namespace trailmix::math::misc {

// Takes X,Y coordinates, and returns a flat array index for the coordinates.
uint32_t array_index(const Vector2u& position, const Vector2u& array_size)
{
    if (position.x >= array_size.x || position.y >= array_size.y)
        throw runtime_error("array_index given invalid coords: " + to_string(position.x) + "," + to_string(position.y));
    else if (!array_size.x || !array_size.y)
        throw runtime_error("array_index given invalid array size: " + to_string(array_size.x) + "," + to_string(array_size.y));
    return (position.y * array_size.x) + position.x;
}

// Calculates the distance between two coordinates in 2D space.
float distance_between(const Vector2& start, const Vector2& end)
{
    const float dx = float(start.x - end.x);
    const float dy = float(start.y - end.y);
    return std::sqrt(dx * dx + dy * dy);
}

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

// Rotates cartesian coordinates by a specified number of radians.
void rotate_cartesian(float *x, float *y, float radians)
{
    const float radius = std::sqrt(((*x) * (*x)) + ((*y) * (*y)));
    const float angle = std::atan2(*y, *x) + radians;
    *x = radius * std::cos(angle);
    *y = radius * std::sin(angle);
}

}   // namespace trailmix::math::misc
