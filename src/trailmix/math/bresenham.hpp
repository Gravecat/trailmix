// math/bresenham.hpp -- Simple implementation of Bresenham's line-drawing algorithm.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <utility>

namespace trailmix {

class BresenhamLine {
public:
    BresenhamLine(int x1, int y1, int x2, int y2);  // Sets up for line calculation.
    std::pair<int, int> step(); // Makes one step along the line.

private:
    int     delta_x_, delta_y_;
    int     sign_x_, sign_y_;
    int     param_;
    bool    swapped_;
    int     x_, y_;
};  // class BresenhamLine

}   // namespace trailmix
