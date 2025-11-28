// math/random.hpp -- Simple interface code to use effolkronium's random number generator.
// Raine "Gravecat" Simmons, 2025.

#pragma once
#include "3rdparty/random/random.hpp"

// get base random alias which is auto seeded and has static API and internal state
namespace trailmix::math { using random = effolkronium::random_static; }
