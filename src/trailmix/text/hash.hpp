// text/hash.hpp -- Simple wrapper code to provide much simpler access to MurmurHash3, for hashing simple strings into integers.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <string>

namespace trailmix::text::hash {

uint32_t    murmur3(const std::string& str);   // Hashes a string with MurmurHash3.

// Only in debug builds, we're gonna add some extra code to detect hash collisions in real-time. Yes, it'll slow performance by a tiny amount, but it's a
// debug build, we're not expecting maximum optimization and speed here.
#ifdef TRAILMIX_BUILD_DEBUG
void        check_hash_collision(const std::string& str, uint32_t hash);
#endif

}   // namespace trailmix::text::hash
