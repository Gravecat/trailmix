// math/rotation.hpp -- Math functions regarding the calculation of rotations.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

namespace trailmix::math::rotation {

void    rotate_cartesian(float *x, float *y, float radians);    // Rotates cartesian coordinates by a specified number of radians.

}   // namespace trailmix::math::rotation
