// math/mathutils.cpp -- Miscellaneous utility files for math and number-related tasks.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/math/mathutils.hpp"

#include <stdexcept>
#include <string>

using std::runtime_error;
using std::to_string;

namespace trailmix {

// Takes X,Y coordinates, and returns a flat array index for the coordinates.
uint32_t array_index(Vector2u position, Vector2u array_size)
{
    if (position.x >= array_size.x || position.y >= array_size.y)
        throw runtime_error("array_index given invalid coords: " + to_string(position.x) + "," + to_string(position.y));
    else if (!array_size.x || !array_size.y) throw runtime_error("array_index given invalid array size: " + to_string(array_size.x) + "," + to_string(array_size.y));
    return (position.y * array_size.x) + position.x;
}

}   // namespace trailmix
