// math/conversion.hpp -- Utility functions for doing verious kinds of conversions on numbers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include "trailmix/math/vector2.hpp"

namespace trailmix::math::conversion {

uint32_t    array_index(const Vector2u& position, const Vector2u& array_size);  // Takes X,Y coordinates, and returns a flat array index for the coordinates.

}   // namespace trailmix::math::conversion
