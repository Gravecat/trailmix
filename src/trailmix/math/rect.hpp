// math/rect.hpp -- The Rect struct provides a simple way of storing and sharing 2D coordinates, in this case for a rectangular area.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <initializer_list>
#include <string>

#include "trailmix/math/vector2.hpp"

namespace trailmix::math {

// Simple struct for a rectangular area on a two-dimensional grid.
struct Rect
{
    Rect() : x(0), y(0), w(0), h(0) { }
    Rect(int32_t rx, int32_t ry, int32_t rw, int32_t rh) : x(rx), y(ry), w(rw), h(rh) { }
    Rect(Vector2 rxy, Vector2 rwh) : x(rxy.x), y(rxy.y), w(rwh.x), h(rwh.y) { }
    Rect(std::initializer_list<int32_t> list)
    {
        auto it = list.begin();
        x = (it != list.end()) ? *it++ : 0;
        y = (it != list.end()) ? *it++ : 0;
        w = (it != list.end()) ? *it++ : 0;
        h = (it != list.end()) ? *it : 0;
    }

    bool        operator==(const Rect &other) const { return (x == other.x && y == other.y && w == other.w && h == other.h); }
    bool        operator!=(const Rect &other) const { return (x != other.x || y != other.y || w != other.w || h != other.h); }
    bool        operator!() const { return (x == 0 && y == 0 && w == 0 && h == 0); }
    bool        operator>(const Rect &other) const { return (w > other.w && h > other.h); }
    bool        operator<(const Rect &other) const { return (w < other.w || h < other.h); }
    bool        operator>(const Vector2 &other) const { return (w > other.x && h > other.y); }
    bool        operator<(const Vector2 &other) const { return (w < other.x || h < other.y); }
    explicit    operator bool() const { return (x != 0 || y != 0 || w != 0 || h != 0); }

    const std::string   to_string() const { return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(w) + "," + std::to_string(h); }

    int32_t x, y, w, h;
};

}   // namespace trailmix::math
