// text/conversion.cpp -- Utility functions for doing verious kinds of conversions on strings.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "trailmix/text/conversion.hpp"

using std::string;

namespace trailmix::text::conversion {

// Converts a bool to a string ("true" or "false").
string bool_to_str(bool b) { return (b ? "true" : "false"); }

// Converts a float or double to a string.
string ftos(double num, int precision)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << num;
    return ss.str();
}

// Converts a number (e.g. 123) into a string (e.g. "one hundred and twenty-three").
string number_to_text(int64_t num)
{
    bool negative = false;
    if (num == 0) return "zero";
    else if (num > 999999999999LL) return "more than nine hundred and ninety-nine billion";
    else if (num < -999999999999LL) return "less than minus nine hundred and ninety-nine billion";
    else if (num < 0)
    {
        negative = true;
        num = -num;
    }

    const string below_twenty[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen",
    "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
    const string tens[] = { "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
    const string scale[] = { "", " thousand", " million", " billion" };

    auto thousand_chunk = [&below_twenty, &tens](int num) -> string {
        string result;
        if (num >= 100)
        {
            result = below_twenty[num / 100] + " hundred";
            num %= 100;
            if (num) result += " and ";
        }
        if (num >= 20)
        {
            result += tens[num / 10];
            if (num % 10) result += "-" + below_twenty[num % 10];
        }
        else if (num > 0 || result.empty()) result += below_twenty[num];
        return result;
    };

    string output;
    int group = 0;
    while(num > 0 && group < 4)
    {
        int chunk = num % 1000;
        num /= 1000;
        if (chunk)
        {
            string result = thousand_chunk(chunk) + scale[group];
            output = result + (output.empty() ? "" : (group > 0 ? ", " : " ") + output);
        }
        group++;
    }
    return (negative ? "minus " : "") + output;
}

// Converts a string to lower-case.
string str_tolower(string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

}   // namespace trailmix::text::conversion
