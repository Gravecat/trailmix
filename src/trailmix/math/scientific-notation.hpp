// math/scientific-notation.hpp -- A class to store very large or small numbers as scientific notation, without being an actual raw float/double value.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <string>

namespace trailmix::math {

class SciNot
{
public:
            SciNot();                       // Creates an empty object with zeroed values.
            SciNot(float f, int p);         // Creates a new scientific notation object.
    double  get_actual() const;             // Getter function for num_actual_
    float   get_float() const;              // Getter function for num_float_
    int     get_power() const;              // Getter function for num_power_
    const std::string get_string() const;   // Gets the number as a string-format scientific notation.
    void    set_value(double d);            // Sets the value directly, then recalculates num_float_ and num_power_
    void    set_values(float f, int p);     // Sets the values for this object, and recalculates num_actual_

private:
    double  num_actual_;    // The 'true' number, stored as a double.
    float   num_float_;     // The float part of the scientific notation.
    int     num_power_;     // The power part of the scientific notation.
};

}   // namespace trailmix::math
