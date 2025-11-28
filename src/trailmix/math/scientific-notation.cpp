// math/scientific-notation.hpp -- A class to store very large or small numbers as scientific notation, without being an actual raw float/double value.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>

#include "trailmix/math/scientific-notation.hpp"
#include "trailmix/text/conversion.hpp"

using namespace trailmix::text::conversion;
using std::string;

namespace trailmix::math {

// Creates an empty object with zeroed values.
SciNot::SciNot() : num_actual_(0), num_float_(0), num_power_(0) { }

// Creates a new scientific notation object.
SciNot::SciNot(float f, int p) { set_values(f, p); }

// Gets the actual number as a double.
double SciNot::get_actual() const { return num_actual_; }

// Getter function for num_float_
float SciNot::get_float() const { return num_float_; }

// Getter function for num_power_
int SciNot::get_power() const { return num_power_; }

// Gets the number as a string-format scientific notation.
const string SciNot::get_string() const
{
    if (num_power_ == 0) return ftos(num_float_);
    else return ftos(num_float_) + " x 10^" + std::to_string(num_power_);
}

// Sets the value directly, then recalculates num_float_ and num_power_
void SciNot::set_value(double d)
{
    num_actual_ = d;
    num_power_ = static_cast<int>(std::log10(std::fabs(d)));
    num_float_ = d / std::pow(10, num_power_);
}

// Sets the values for this object, and recalculates num_actual_
void SciNot::set_values(float f, int p)
{
    num_float_ = f;
    num_power_ = p;
    num_actual_ = std::pow(static_cast<double>(f), static_cast<double>(p));
}

}   // namespace trailmix::math
