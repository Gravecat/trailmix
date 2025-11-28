// math/voronoi.hpp -- Very simple Voronoi diagram generation.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "trailmix/math/vector2.hpp"

namespace trailmix::math {

class VoronoiDiagram
{
public:
                        VoronoiDiagram(double w, double h);
    void                add_site(double x, double y);
    double              get_cell_area(int id, int grid_size) const; // grid_size = number of samples in each dimension
    size_t              get_cell_count() const;
    int                 get_cell_id(double x, double y) const;
    int                 get_edges_touching_boundary(int cell_id) const;
    double              get_height() const;
    std::vector<int>    get_neighboring_cells(int cell_id) const;
    double              get_width() const;

private:
    Vector2             get_two_closest_sites(double x, double y) const;    // Helper function to get the two closest sites to a point

    double  width_, height_;
    std::vector<Vector2>    sites_;
};

}   // namespace trailmix::math
