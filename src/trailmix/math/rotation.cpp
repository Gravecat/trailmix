// math/rotation.cpp -- Math functions regarding the calculation of rotations.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/rotation.hpp"

namespace trailmix::math::rotation {

// Calculates orbital position around an origin point.
std::pair<double, double> calculate_orbit(double origin_x, double origin_y, double rotation, double distance)
{
    const double out_x = (distance * std::sin(M_PI * 2.0f * rotation / 360.0f)) + origin_x;
    const double out_y = (distance * std::cos(M_PI * 2.0f * rotation / 360.0f)) + origin_y;
    return std::pair<double, double>(out_x, out_y);
}

// Rotates cartesian coordinates by a specified number of radians.
void rotate_cartesian(float *x, float *y, float radians)
{
    const float radius = std::sqrt(((*x) * (*x)) + ((*y) * (*y)));
    const float angle = std::atan2(*y, *x) + radians;
    *x = radius * std::cos(angle);
    *y = radius * std::sin(angle);
}

}   // namespace trailmix::math::rotation
