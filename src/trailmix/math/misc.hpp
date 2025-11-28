// math/misc.hpp -- Miscellaneous utility files for math and number-related tasks.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "trailmix/math/vector2.hpp"

namespace trailmix::math::misc {

uint32_t    array_index(Vector2u position, Vector2u array_size);    // Takes X,Y coordinates, and returns a flat array index for the coordinates.
float       distance_between(const Vector2& start, const Vector2& end); // Calculates the distance between two coordinates in 2D space.
uint32_t    mixup(unsigned int num, bool big_mix = false);  // Mixes up an integer a little.
void        rotate_cartesian(float *x, float *y, float radians);    // Rotates cartesian coordinates by a specified number of radians.

}   // namespace trailmix::math::misc
