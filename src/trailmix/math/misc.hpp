// math/misc.hpp -- Miscellaneous utility files for math and number-related tasks.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "trailmix/math/vector2.hpp"

namespace trailmix::math::misc {

float       distance_between(const Vector2& start, const Vector2& end); // Calculates the distance between two coordinates in 2D space.

}   // namespace trailmix::math::misc
