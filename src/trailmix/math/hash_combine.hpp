// math/hash_combine.hpp -- Used internally by Vector2, Vector2u and Vector3 to work with std::hash.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>

namespace trailmix {

inline void hash_combine(std::size_t& seed, std::size_t h) noexcept
{ seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2); }

}   // namespace trailmix
