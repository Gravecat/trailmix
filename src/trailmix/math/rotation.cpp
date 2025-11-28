// math/rotation.cpp -- Math functions regarding the calculation of rotations.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/rotation.hpp"

namespace trailmix::math::rotation {

// Rotates cartesian coordinates by a specified number of radians.
void rotate_cartesian(float *x, float *y, float radians)
{
    const float radius = std::sqrt(((*x) * (*x)) + ((*y) * (*y)));
    const float angle = std::atan2(*y, *x) + radians;
    *x = radius * std::cos(angle);
    *y = radius * std::sin(angle);
}

}   // namespace trailmix::math::rotation
