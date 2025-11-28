// math/perlin.hpp -- Simple Perlin noise generator. It's honestly not that great, there's better options out there for Perlin noise.
// I don't really remember how this works anymore, it's salvaged from some very old project code of mine.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

namespace trailmix::math::perlin {

double          perlin(double x, double y, double zoom, double p, int octaves); // Ordinary Perlin genertion routine, though I'm not entirely sure how it works.
double          perlin_findnoise2(double x, double y);  // Pseudo-random number generator for Perlin noise generation.
double          perlin_interpolate(double a, double b, double x);   // Cosine interpolation.
double          perlin_noise(double x, double y);   // Generate noise for a given coordinate?
unsigned char   perlin_rgb(double x, double y, double zoom, double p, int octaves); // Wrapper to generate a 0-255 RGB value for the given coord.

}   // namespace trailmix::math::perlin
