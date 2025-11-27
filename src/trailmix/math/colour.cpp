// math/colour.cpp -- Functions for adjusting or converting colour values.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/colour.hpp"

using std::round;

namespace trailmix {
namespace colour {

// Converts HSB colour to RGB.
RGB hsb_to_rgb(float hue, float saturation, float brightness)
{
    float red = 0, green = 0, blue = 0;
    if (!saturation) red = green = blue = brightness;
    else
    {
        if (hue >= 360) hue = 0;
        int slice = hue / 60.0f;
        float hue_frac = (hue / 60.0f) - slice;
        float aa = brightness * (1.0f - saturation);
        float bb = brightness * (1.0f - (saturation * hue_frac));
        float cc = brightness * (1.0f - (saturation * (1.0f - hue_frac)));
        switch (slice)
        {
            case 0: red = brightness; green = cc; blue = aa; break;
            case 1: red = bb; green = brightness; blue = aa; break;
            case 2: red = aa; green = brightness; blue = cc; break;
            case 3: red = aa; green = bb; blue = brightness; break;
            case 4: red = cc; green = aa; blue = brightness; break;
            case 5: red = brightness; green = aa; blue = bb; break;
            default: red = green = blue = 0; break;
        }
    }
    return { static_cast<uint8_t>(round(red * 255.0f)), static_cast<uint8_t>(round(green * 255.0f)),
        static_cast<uint8_t>(round(blue * 255.0f)) };
}

} } // colour, trailmix namespaces
