// text/conversion.cpp -- Utility functions for doing verious kinds of conversions on strings.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include "trailmix/text/conversion.hpp"

using std::runtime_error;
using std::string;
using std::to_string;
using std::vector;

namespace trailmix::text::conversion {

// Converts a bool to a string ("true" or "false").
string bool_to_str(bool b) { return (b ? "true" : "false"); }

// Simple function to collapse a string vector into words.
string collapse_vector(vector<string> vec)
{
    std::ostringstream output;
    if (!vec.empty())
    {
        std::copy(vec.begin(), vec.end() - 1, std::ostream_iterator<string>(output, " "));
        output << vec.back();
    }
    return output.str();
}

// As above, but for an integer vector>
string collapse_vector(vector<int> vec)
{
    vector<string> converted_vec;
    for (auto i : vec)
        converted_vec.push_back(to_string(i));
    return collapse_vector(converted_vec);
}

// Converts a float or double to a string.
string ftos(double num, int precision)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << num;
    return ss.str();
}

// Converts a hex string into an integer.
uint32_t htoi(const string& hex_str)
{
	std::stringstream ss;
	ss << std::hex << hex_str;
	uint32_t result;
	ss >> result;
	return result;
}

// Returns a 'pretty' version of a number in string format, such as "12,345".
string intostr_pretty(int num)
{
    bool negative = false;
    if (num < 0)
    {
        negative = true;
        num = 0 - num;
    }
    string str = std::to_string(num), output;

    // If the number is 3 or less characters long, there's no need for any processing.
    if (str.length() <= 3) return((negative ? "-" : "") + str);

    do
    {
        // Cut the string up, and insert commas where appropriate.
        output = str.substr(str.length() - 3, 3) + "," + output;
    str = str.substr(0, str.length() - 3);
    } while (str.length() > 3);

    // Combine the results.
    string result = str + "," + output;

    // Remove the trailing comma.
    result = result.substr(0, result.length() - 1);

    return((negative ? "-" : "") + result);
}

// Unsigned 64-bit version.
string intostr_pretty_u64(uint64_t num)
{
    string str = to_string(num), output;

    // If the number is 3 or less characters long, there's no need for any processing.
    if (str.length() <= 3) return str;

    do
    {
        // Cut the string up, and insert commas where appropriate.
        output = str.substr(str.length() - 3, 3) + "," + output;
        str = str.substr(0, str.length() - 3);
    } while(str.length() > 3);

    // Combine the results.
    std::string result = str + "," + output;

    // Remove the trailing comma.
    result = result.substr(0, result.length() - 1);
    return result;
}

// Converts a nummber (like 5 or -3) to one that always has a sign (e.g. +5 or -3).
string intostr_sign(int num)
{
    if (num < 0) return intostr_pretty(num);
    else return "+" + intostr_pretty(num);
}

// Converts an integer into a hex string.
string itoh(uint32_t num, uint8_t min_len)
{
    std::stringstream ss;
    ss << std::hex << num;
    string hex = ss.str();
    while (min_len && hex.size() < min_len) hex = "0" + hex;
    return hex;
}

// Converts an integer to a string, but optionally pads it to a minimum length with leading zeroes.
string itos(uint32_t num, size_t min_len)
{
    string result = to_string(num);
    while (result.size() < min_len) result = "0" + result;
    return result;
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

// Converts an integer to a string; handles out-of-range values gracefully.
int32_t stoi(const string& str)
{
    try { return (std::stoll(str)); }
    catch(const std::exception&) { return INT32_MAX; }
}

// Converts a std::string vector into a int vector.
vector<int> stoi_vec(const vector<string>& vec)
{
    std::vector<int> output;
    for (auto str : vec)
        output.push_back(conversion::stoi(str));
    return output;
}

// Converts a string to a bool.
bool str_to_bool(const string& str)
{
    if (!str.size()) return false;
    switch (str[0])
    {
        case '0': case 'f': case 'F': case 'n': case 'N': case '-': return false;
        case '1': case 't': case 'T': case 'y': case 'Y': return true;
        default: throw runtime_error("Invalid boolean string: " + str);
    }
}

// Returns a time string as a rough description ("a few seconds", "a moment", "a few minutes").
string time_string_rough(float seconds)
{
    if (seconds < 1.0f) return "a moment";
    else if (seconds < 2.0f) return "a second";
    else if (seconds < 5.0f) return "a couple of seconds";
    else if (seconds < 10.0f) return "a few seconds";
    else if (seconds < 20.0f) return "about ten seconds";
    else if (seconds < 30.0f) return "about twenty seconds";
    else if (seconds < 60.0f) return "half a minute";
    else if (seconds < 120.0f) return "a minute";
    else if (seconds < 900.0f) return "a few minutes";
    else if (seconds < 1800.0f) return "a quarter of an hour";
    else if (seconds < 2700.0f) return "half an hour";
    else if (seconds < 3600.0f) return "three quarters of an hour";
    else if (seconds < 7200.0f) return "an hour";
    else if (seconds < 10800.0f) return "a couple of hours";
    else if (seconds < 43200.0f) return "several hours";
    else if (seconds < 82800.0f) return "half a day";
    else if (seconds < 86400.0f) return "most of a day";
    else if (seconds < 172800.0f) return "a day";
    else if (seconds < 259200.0f) return "a couple of days";
    else if (seconds < 604800.0f) return "several days";
    else if (seconds < 1209600.0f) return "a week";
    else if (seconds < 2592000.0f) return "weeks";
    else if (seconds < 5184000.0f) return "a month";
    else if (seconds < 31536000.0f) return "months";
    else if (seconds < 63072000.0f) return "a year";
    else return "years";
}

// Converts a string to a wstring.
std::wstring to_wstring(const string &str) { return std::wstring(str.begin(), str.end()); }

}   // namespace trailmix::text::conversion
