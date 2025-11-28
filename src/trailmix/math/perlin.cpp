// math/perlin.cpp -- Simple Perlin noise generator. It's honestly not that great, there's better options out there for Perlin noise.
// I don't really remember how this works anymore, it's salvaged from some very old project code of mine.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/perlin.hpp"

namespace trailmix::math::perlin {

// Ordinary Perlin genertion routine, though I'm not entirely sure how it works.
double perlin(double x, double y, double zoom, double p, int octaves)
{
    double getnoise = 0.0;
    for (int a = 0; a < octaves - 1; a++)   // This loops trough the octaves.
    {
        const double frequency = std::pow(2, a);    // This increases the frequency with every loop of the octave.
        const double amplitude = std::pow(p, a);    // This decreases the amplitude with every loop of the octave.
        // This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude.
        // It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1.
        getnoise += perlin_noise(x * frequency / zoom, y / zoom * frequency) * amplitude;
    }
    return getnoise;
}

// Pseudo-random number generator for Perlin noise generation.
double perlin_findnoise2(double x, double y)
{
    long long n = static_cast<long long>(x) + static_cast<long long>(y) * 57;
    n = (n << 13) ^ n;
    const long long nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return 1.0 - (static_cast<double>(nn) / 1073741824.0f);
}

// Cosine interpolation.
double perlin_interpolate(double a, double b, double x)
{
    const double ft = x * M_PI;
    const double f = (1.0 - cos(ft)) * 0.5;
    return a * (1.0 - f) + b * f;
}

// Generate noise for a given coordinate?
double perlin_noise(double x, double y)
{
    const double floorx = static_cast<double>(static_cast<long long>(x));   // This is kinda a cheap way to floor a double integer.
    const double floory = static_cast<double>(static_cast<long long>(y));
    double s, t, u, v;  // Integer declaration
    s = perlin_findnoise2(floorx, floory);
    t = perlin_findnoise2(floorx + 1, floory);
    u = perlin_findnoise2(floorx, floory + 1);  // Get the surrounding pixels to calculate the transition.
    v = perlin_findnoise2(floorx + 1, floory + 1);
    const double int1 = perlin_interpolate(s, t, x - floorx);   // Interpolate between the values.
    // Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.
    const double int2 = perlin_interpolate(u, v, x - floorx);
    return perlin_interpolate(int1, int2, y - floory);  // Here we use y-floory, to get the 2nd dimension.
}

// Wrapper to generate a 0-255 RGB value for the given coord. I wrote some of this, butchered some. It's flakey and weird, don't fuck with it.
unsigned char perlin_rgb(double x, double y, double zoom, double p, int octaves)
{
    const double getnoise = perlin(x, y, zoom, p, octaves);
    int color = static_cast<int>((getnoise * 128.0f) + 128.0f); // Convert to 0-256 values.
    if (color > 255) color = 255;
    if (color < 0) color = 0;
    return static_cast<unsigned char>(color);
}

}   // namespace trailmix::math::perlin
