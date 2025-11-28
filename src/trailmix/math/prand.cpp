// math/prand.cpp -- Seedable, predictable pseudo-random number generator. Not great for true randomness, great for predictable, reusable results.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/math/prand.hpp"

namespace trailmix::math {

// Creates a new pseudo-random number generator, setting the seed to a default 0.
PRand::PRand() : seed_(0) { }

// As above, but specifies a seed.
PRand::PRand(uint32_t seed) : seed_(seed) { }

// Gets a random number between 0 and lim.
unsigned int PRand::get(unsigned int lim)
{
    if (!lim) return 0;
    seed_ = (seed_ * 0x43FD43FD + 0xC39EC3) & 0xFFFFFF;
    const float tmp = static_cast<float>(seed_) / 16777216.0f;
    return static_cast<unsigned int>(tmp * lim);
}

// Sets a new PRNG seed.
void PRand::set_seed(uint32_t seed) { seed_ = seed; }

}   // namespace trailmix::math
