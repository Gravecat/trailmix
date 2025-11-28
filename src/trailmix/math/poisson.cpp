// math/poisson.cpp -- Poisson disk sampler algorithm, to generate points on a grid with a relatively uniform distribution.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/poisson.hpp"
#include "trailmix/math/random.hpp"
#include "trailmix/math/mathutils.hpp"

using std::vector;

namespace trailmix::math {

PoissonDiskSampler::PoissonDiskSampler(int w, int h, float min_dist) : min_distance_(min_dist), width_(w), height_(h)
{
    cell_size_ = min_distance_ / std::sqrt(2.0f);
    grid_width_ = std::ceil(width_ / cell_size_);
    grid_height_ = std::ceil(height_ / cell_size_);
    grid_.resize(grid_height_, vector<int>(grid_width_, -1));
}

vector<Vector2> PoissonDiskSampler::generate_points(unsigned int num_points, const vector<Vector2>& existing_points)
{
    points_.clear();
    // Reset grid
    for (auto& row : grid_)
        std::fill(row.begin(), row.end(), -1);

    // Add existing points
    for (const Vector2& p : existing_points) {
        if (p.x >= 0 && p.x < width_ && p.y >= 0 && p.y < height_)
        {
            points_.push_back(p);
            const int grid_index = point_to_grid(p);
            if (grid_index != -1) grid_[grid_index / grid_width_][grid_index % grid_width_] = points_.size() - 1;
        }
    }

    vector<Vector2> active_points;

    // Start with a random point if no existing points
    if (points_.empty())
    {
        Vector2 first_point(random::get(0, width_ - 1), random::get(0, height_ - 1));
        points_.push_back(first_point);
        active_points.push_back(first_point);
        grid_[point_to_grid(first_point) / grid_width_][point_to_grid(first_point) % grid_width_] = 0;
    } else active_points = points_;

    // Generate remaining points
    while (!active_points.empty() && points_.size() < num_points)
    {
        Vector2 current_point = active_points[random::get<unsigned int>(0, active_points.size() - 1)];
        bool foundValid = false;

        // Try to generate new points around the current point
        for (int i = 0; i < 30; ++i)
        {
            Vector2 candidate_point = generate_random_point_around(current_point);
            if (is_valid_point(candidate_point))
            {
                points_.push_back(candidate_point);
                active_points.push_back(candidate_point);
                grid_[point_to_grid(candidate_point) / grid_width_][point_to_grid(candidate_point) % grid_width_] = points_.size() - 1;
                foundValid = true;
                break;
            }
        }

        if (!foundValid) active_points.erase(active_points.begin() + random::get<unsigned int>(0, active_points.size() - 1));
    }

    return points_;
}

Vector2 PoissonDiskSampler::generate_random_point_around(const Vector2& center)
{
    const float radius = min_distance_ * (1.0f + random::get(0.0f, 1.0f));
    const float angle = random::get(0.0f, 1.0f) * 2.0f * M_PI;

    const int new_x = center.x + static_cast<int>(radius * std::cos(angle));
    const int new_y = center.y + static_cast<int>(radius * std::sin(angle));

    return Vector2(new_x, new_y);
}

bool PoissonDiskSampler::is_valid_point(const Vector2& p) const
{
    if (p.x < 0 || p.x >= width_ || p.y < 0 || p.y >= height_) return false;

    int grid_index = point_to_grid(p);
    if (grid_index == -1) return false;

    // Check nearby cells for minimum distance
    const int grid_x = grid_index % grid_width_;
    const int grid_y = grid_index / grid_width_;

    for (int dy = -2; dy <= 2; dy++)
    {
        for (int dx = -2; dx <= 2; dx++)
        {
            const int new_grid_x = grid_x + dx;
            const int new_grid_y = grid_y + dy;

            if (new_grid_x >= 0 && new_grid_x < grid_width_ && new_grid_y >= 0 && new_grid_y < grid_height_)
            {
                const int idx = grid_[new_grid_y][new_grid_x];
                if (idx != -1 && math::utils::distance_between(p, points_[idx]) < min_distance_) return false;
            }
        }
    }
    return true;
}

int PoissonDiskSampler::point_to_grid(const Vector2& p) const
{
    const int grid_x = p.x / cell_size_;
    const int grid_y = p.y / cell_size_;
    if (grid_x < 0 || grid_x >= grid_width_ || grid_y < 0 || grid_y >= grid_height_) return -1;
    return grid_y * grid_width_ + grid_x;
}

}   // namespace trailmix::math
