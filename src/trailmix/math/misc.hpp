// math/misc.hpp -- Miscellaneous utility files for math and number-related tasks.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "trailmix/math/vector2.hpp"

namespace trailmix::math::misc {

uint32_t    array_index(const Vector2u& position, const Vector2u& array_size);  // Takes X,Y coordinates, and returns a flat array index for the coordinates.
float       distance_between(const Vector2& start, const Vector2& end); // Calculates the distance between two coordinates in 2D space.
double      lerp(double a, double b, double f); // Interpolates between two floating point values.
uint32_t    mixup(unsigned int num, bool big_mix = false);  // Mixes up an integer a little.
double      round_to(double num, unsigned int digits);  // Rounds a float to a specified number of digits.

}   // namespace trailmix::math::misc
