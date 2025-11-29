// math/random.cpp -- Simple interface code to use effolkronium's random number generator.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include "trailmix/math/random.hpp"

namespace trailmix::math::rng {

// Flips a coin - heads is true, tails is false.
bool coin_flip() { return rnd::get<bool>(0.5f); }

// 'Rolls' a number of dice with an optional modifier (e.g. 4d6+3).
int roll(unsigned int num_dice, unsigned int die_faces, int modifier)
{
    if (!num_dice || !die_faces) return 0;
    int total = 0;
    for (unsigned int r = 0; r < num_dice; r++)
        total += rnd::get<int>(1, die_faces);
    return total + modifier;
}

}   // namespace trailmix::math::rng
