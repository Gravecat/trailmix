// math/comparison.cpp -- Functions for comparing numbers to other things.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/comparison.hpp"

namespace trailmix::math::comparison {

// Calculates the distance between two coordinates in 2D space.
float distance_between(const Vector2& start, const Vector2& end)
{
    const float dx = float(start.x - end.x);
    const float dy = float(start.y - end.y);
    return std::sqrt(dx * dx + dy * dy);
}

}   // trailmix::math::comparison
