// math/conversion.cpp -- Utility functions for doing verious kinds of conversions on numbers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>
#include <stdexcept>
#include <string>

#include "trailmix/math/conversion.hpp"

using std::runtime_error;
using std::to_string;

namespace trailmix::math::conversion {

// Takes X,Y coordinates, and returns a flat array index for the coordinates.
uint32_t array_index(const Vector2u& position, const Vector2u& array_size)
{
    if (position.x >= array_size.x || position.y >= array_size.y)
        throw runtime_error("array_index given invalid coords: " + to_string(position.x) + "," + to_string(position.y));
    else if (!array_size.x || !array_size.y)
        throw runtime_error("array_index given invalid array size: " + to_string(array_size.x) + "," + to_string(array_size.y));
    return (position.y * array_size.x) + position.x;
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

// Rounds a float to two decimal places. Quicker than calling round_to(..., 2)
float round_to_two(float num) { return ::floorf(num * 100 + 0.5) / 100; }

// Ensures a number fits into an unsigned char (0-255), discarding any values below 0 or above 255.
uint8_t round_to_uchar(int num) { return std::min(std::max(num, 0), 255); }

}   // namespace trailmix::math::conversion
