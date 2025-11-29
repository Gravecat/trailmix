// math/random.hpp -- Simple interface code to use effolkronium's random number generator.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once
#include "3rdparty/random/random.hpp"

// get base random alias which is auto seeded and has static API and internal state
namespace trailmix::math { using rnd = effolkronium::random_static; }

namespace trailmix::math::rng {

bool    coin_flip();    // Flips a coin - heads is true, tails is false.
int     roll(unsigned int num_dice, unsigned int die_faces, int modifier = 0);  // 'Rolls' a number of dice with an optional modifier (e.g. 4d6+3).

// The following functions are just lazy ways of accessing roll() above, with common die types.
inline int d4(unsigned int num_dice = 1, int modifier = 0) { return roll(num_dice, 4, modifier); }
inline int d6(unsigned int num_dice = 1, int modifier = 0) { return roll(num_dice, 6, modifier); }
inline int d8(unsigned int num_dice = 1, int modifier = 0) { return roll(num_dice, 8, modifier); }
inline int d10(unsigned int num_dice = 1, int modifier = 0) { return roll(num_dice, 10, modifier); }
inline int d12(unsigned int num_dice = 1, int modifier = 0) { return roll(num_dice, 12, modifier); }
inline int d20(unsigned int num_dice = 1, int modifier = 0) { return roll(num_dice, 20, modifier); }
inline int d100(unsigned int num_dice = 1, int modifier = 0) { return roll(num_dice, 100, modifier); }

}   // namespace trailmix::math::rng
