// text/hash.cpp -- Simple wrapper code to provide much simpler access to MurmurHash3, for hashing simple strings into integers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#ifdef TRAILMIX_BUILD_DEBUG
#include <iostream>
#include <map>
#endif

#include "3rdparty/murmurhash3/MurmurHash3.h"
#include "trailmix/text/hash.hpp"

using std::string;
using std::to_string;

namespace trailmix::text::hash {

// Hashes a string with MurmurHash3.
uint32_t murmur3(const string& str)
{
    const uint32_t seed = 0x9747b28c;
    uint32_t hash = 0;  // Shouldn't matter, but I don't like uninitialized variables on principle.
    MurmurHash3_x86_32(str.data(), static_cast<int>(str.size()), seed, &hash);

#ifdef TRAILMIX_BUILD_DEBUG
    check_hash_collision(str, hash);
#endif

    return hash;
}

// Only in debug builds, we're gonna add some extra code to detect hash collisions in real-time. Yes, it'll slow performance by a tiny amount, but it's a
// debug build, we're not expecting maximum optimization and speed here.
#ifdef TRAILMIX_BUILD_DEBUG
std::map<uint32_t, string> backward_hash_map;

void check_hash_collision(const string& str, uint32_t hash)
{
    auto result_b = backward_hash_map.find(hash);
    if (result_b == backward_hash_map.end())
    {
        backward_hash_map.insert({hash, str});
        return;
    }
    if (!result_b->second.compare(str)) return;
   std::cerr << "Hash collision detected! " + str + " and " + result_b->second + " both hash to " + to_string(hash);
}
#endif  // TRAILMIX_BUILD_DEBUG

}   // namespace trailmix::text::hash
