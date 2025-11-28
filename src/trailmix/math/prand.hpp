// math/prand.hpp -- Seedable, predictable pseudo-random number generator. Not great for true randomness, great for predictable, reusable results.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace trailmix::math {

class PRand {
public:
                    PRand();                    // Creates a new pseudo-random number generator, setting the seed to a default 0.
                    PRand(uint32_t seed);       // As above, but specifies a seed.
    unsigned int    get(unsigned int lim);      // Gets a random number between 0 and lim.
    void            set_seed(uint32_t seed);    // Sets a new PRNG seed.

private:
    uint32_t    seed_;  // The current PRNG seed.
};

}   // namespace trailmix::math
