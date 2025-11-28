// math/mathutils.hpp -- Miscellaneous utility files for math and number-related tasks.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "trailmix/math/vector2.hpp"

namespace trailmix::math::utils {

uint32_t    array_index(Vector2u position, Vector2u array_size);    // Takes X,Y coordinates, and returns a flat array index for the coordinates.

}   // namespace trailmix::math::utils
