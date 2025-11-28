// text/stringutils.cpp -- Various utility functions that deal with string manipulation/conversion.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <algorithm>

#include "trailmix/text/ansiutils.hpp"
#include "trailmix/text/stringutils.hpp"

using std::string;
using std::transform;
using std::vector;

namespace trailmix::text::utils {

// Converts a vector to a comma-separated list.
string comma_list(vector<string> vec, uint8_t mode)
{
    string plus = ", ";
    if (mode == CL_MODE_USE_AND) plus = " and ";
    else if (mode == CL_MODE_USE_OR) plus = " or ";
    else if (vec.size() == 2) return vec.at(0) + plus + vec.at(1);

    string str;
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        str += vec.at(i);
        if (i < vec.size() - 1)
        {
            if (i == vec.size() - 2) str += plus;
            else str += ", ";
        }
    }
    return str;
}

// Decodes a compressed string (e.g. 4cab2z becomes ccccabzz).
string decode_compressed_string(string cb)
{
    string result;
    while(cb.size())
    {
        string letter = cb.substr(0, 1);
        cb = cb.substr(1);
        if (letter[0] >= '0' && letter[0] <= '9')
        {
            int number = letter[0] - '0';
            letter = cb.substr(0, 1);
            cb = cb.substr(1);
            while (letter[0] >= '0' && letter[0] <= '9')
            {
                number *= 10;
                number += letter[0] - '0';
                letter = cb.substr(0, 1);
                cb = cb.substr(1);
            }
            result += string(number, letter[0]);
        }
        else result += letter;
    }
    return result;
}

// Find and replace one string with another.
bool find_and_replace(string &input, const string &to_find, const string &to_replace)
{
    string::size_type pos = 0;
    const string::size_type find_len = to_find.length(), replace_len = to_replace.length();
    if (find_len == 0) return false;
    bool found = false;
    while ((pos = input.find(to_find, pos)) != string::npos)
    {
        found = true;
        input.replace(pos, find_len, to_replace);
        pos += replace_len;
    }
    return found;
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
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// String split/explode function.
vector<string> string_explode(string str, const string& separator)
{
    vector<string> results;

    string::size_type pos = str.find(separator, 0);
    const size_t pit = separator.length();

    while(pos != string::npos)
    {
        if (pos == 0) results.push_back("");
        else results.push_back(str.substr(0, pos));
        str.erase(0, pos + pit);
        pos = str.find(separator, 0);
    }
    results.push_back(str);

    return results;
}

// Strips trailing newlines from a given string.
string strip_trailing_newlines(string str)
{
    while (!str.empty() && (str.back() == '\n' || str.back() == '\r'))
        str.pop_back();
    return str;
}

}   // namespace trailmix::text::utils
