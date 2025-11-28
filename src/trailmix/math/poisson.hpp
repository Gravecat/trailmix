// math/poisson.hpp -- Poisson disk sampler algorithm, to generate points on a grid with a relatively uniform distribution.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <vector>

#include "trailmix/math/vector2.hpp"

namespace trailmix::math {

class PoissonDiskSampler
{
public:
                            PoissonDiskSampler(int w, int h, float min_dist);
    std::vector<Vector2>    generate_points(unsigned int num_points, const std::vector<Vector2>& existing_points = {});

private:
    Vector2 generate_random_point_around(const Vector2& center);
    bool    is_valid_point(const Vector2& p) const;
    int     point_to_grid(const Vector2& p) const;

    float   cell_size_;
    int     grid_width_, grid_height_;
    float   min_distance_;
    int     width_, height_;
    std::vector<std::vector<int>>   grid_;
    std::vector<Vector2>    points_;
};

}   // namespace trailmix::math
