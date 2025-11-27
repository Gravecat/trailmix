// math/colour.hpp -- Functions for adjusting or converting colour values.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace trailmix {
namespace colour {

// Simple RGB colour struct.
struct RGB { uint8_t r, g, b; };

RGB hsb_to_rgb(float hue, float saturation, float brightness);  // Converts HSB colour to RGB.

} } // colour, trailmix namespaces
