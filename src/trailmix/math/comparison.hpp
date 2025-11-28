// math/comparison.hpp -- Functions for comparing numbers to other things.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "trailmix/math/vector2.hpp"
#include "trailmix/math/vector3.hpp"

namespace trailmix::math::comparison {

float   distance_between(const Vector2& start, const Vector2& end); // Calculates the distance between two coordinates in 2D space.
float   distance_between(const Vector3& start, const Vector3& end); // As above, but for a three-dimensional grid.

}   // trailmix::math::comparison
