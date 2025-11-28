// math/voronoi.cpp -- Very simple Voronoi diagram generation.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>
#include <cstddef>
#include <set>
#include <utility>
#include <vector>

#include "trailmix/math/mathutils.hpp"
#include "trailmix/math/voronoi.hpp"

using namespace trailmix::math::utils;
using std::vector;

namespace trailmix::math {

VoronoiDiagram::VoronoiDiagram(double w, double h) : width_(w), height_(h) { }

void VoronoiDiagram::add_site(double x, double y)
{
    if (x >= 0 && x <= width_ && y >= 0 && y <= height_)
        sites_.emplace_back(x, y);
}

double VoronoiDiagram::get_cell_area(int id, int grid_size) const
{
    if (id < 0 || id >= static_cast<int>(sites_.size())) return 0.0;

    const double dx = width_ / grid_size;
    const double dy = height_ / grid_size;
    int points_in_cell = 0;

    // Sample points in a grid
    for (int y = 0; y < grid_size; y++)
    {
        for (int x = 0; x < grid_size; x++)
        {
            double px = x * dx + dx/2;  // Center of grid cell
            double py = y * dy + dy/2;

            if (get_cell_id(px, py) == id) points_in_cell++;
        }
    }

    // Calculate area based on proportion of points in cell
    double totalArea = width_ * height_;
    double cellArea = totalArea * (points_in_cell / static_cast<double>(grid_size * grid_size));

    return cellArea;
}

int VoronoiDiagram::get_cell_id(double x, double y) const
{
    if (x < 0 || x > width_ || y < 0 || y > height_ || sites_.empty()) return -1;

    Vector2 query(x, y);
    int closest_site = 0;
    double min_distance =  distance_between(sites_[0], query);

    for (size_t i = 1; i < sites_.size(); ++i)
    {
        double distance = distance_between(sites_[i], query);
        if (distance < min_distance)
        {
            min_distance = distance;
            closest_site = i;
        }
    }

    return closest_site;
}

int VoronoiDiagram::get_edges_touching_boundary(int cell_id) const
{
    if (cell_id < 0 || cell_id >= static_cast<int>(sites_.size())) return 0;

    std::set<int> boundary_edges;   // 0=left, 1=top, 2=right, 3=bottom
    const int samples = 50; // Sample points along each boundary

    // Check left edge (x = 0)
    for (int i = 0; i < samples; i++)
    {
        double y = (height_ * i) / (samples - 1);
        if (get_cell_id(0, y) == cell_id) boundary_edges.insert(0);
    }

    // Check right edge (x = width)
    for (int i = 0; i < samples; i++)
    {
        double y = (height_ * i) / (samples - 1);
        if (get_cell_id(width_, y) == cell_id) boundary_edges.insert(2);
    }

    // Check top edge (y = 0)
    for (int i = 0; i < samples; i++)
    {
        double x = (width_ * i) / (samples - 1);
        if (get_cell_id(x, 0) == cell_id) boundary_edges.insert(1);
    }

    // Check bottom edge (y = height)
    for (int i = 0; i < samples; i++)
    {
        double x = (width_ * i) / (samples - 1);
        if (get_cell_id(x, height_) == cell_id) boundary_edges.insert(3);
    }

    return boundary_edges.size();
}

double VoronoiDiagram::get_height() const { return height_; }

vector<int> VoronoiDiagram::get_neighboring_cells(int cell_id) const
{
    if (cell_id < 0 || cell_id >= static_cast<int>(sites_.size())) return {};

    std::set<int> neighbors;
    const int samples = 100;    // Number of sample points to check
    const double margin = 0.1;  // Small offset to avoid edge cases

    // Sample points in a circle around the site
    Vector2 center = sites_[cell_id];
    double max_radius = std::max(width_, height_);  // Maximum possible radius

    for (int i = 0; i < samples; ++i) {
        double angle = (2.0 * M_PI * i) / samples;
        for (double r = 0; r < max_radius; r += max_radius/20)
        {
            const double x = center.x + (r + margin) * std::cos(angle);
            const double y = center.y + (r + margin) * std::sin(angle);

            // Skip points outside the diagram
            if (x < 0 || x > width_ || y < 0 || y > height_) continue;

            // Get the two closest sites to this point
            auto [closest, second] = get_two_closest_sites(x, y);

            // If one of them is our cell and the other isn't, we've found a neighbor
            if (closest == cell_id && second != -1) neighbors.insert(second);
            else if (second == cell_id && closest != -1) neighbors.insert(closest);
        }
    }

    return vector<int>(neighbors.begin(), neighbors.end());
}

// Helper function to get the two closest sites to a point
Vector2 VoronoiDiagram::get_two_closest_sites(double x, double y) const
{
    Vector2 query(x, y);
    int closest = -1;
    int second_closest = -1;
    double min_dist = std::numeric_limits<double>::max();
    double second_min_dist = std::numeric_limits<double>::max();

    for (size_t i = 0; i < sites_.size(); ++i)
    {
        const double dist = distance_between(sites_[i], query);
        if (dist < min_dist)
        {
            second_closest = closest;
            second_min_dist = min_dist;
            closest = i;
            min_dist = dist;
        }
        else if (dist < second_min_dist)
        {
            second_closest = i;
            second_min_dist = dist;
        }
    }

    return {closest, second_closest};
}

double VoronoiDiagram::get_width() const { return width_; }

}   // namespace trailmix::math
