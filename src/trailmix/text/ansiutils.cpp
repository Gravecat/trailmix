// text/ansiutils.cpp -- Various utility functions that deal with string manipulation/conversion -- in particular, strings that use a special type of tags I use in my own projects
// for marking where ANSI colour codes will be inserted into text.

// SPDX-FileType: SOURCE
// SPDX-FileCopyrightText: Copyright 2025 Raine Simmons <gc@gravecat.com>
// SPDX-License-Identifier: MIT

#include <cmath>
#include <stdexcept>

#include "trailmix/text/ansiutils.hpp"
#include "trailmix/text/comparison.hpp"
#include "trailmix/text/manipulation.hpp"

using namespace trailmix::text::comparison;
using namespace trailmix::text::manipulation;
using std::runtime_error;
using std::string;
using std::vector;

namespace trailmix::text::ansi {

// Centres all the strings in a vector.
uint32_t ansi_centre_strvec(vector<string>& vec)
{
    uint32_t longest = 0;
    for (auto line : vec)
    {
        unsigned int len = ansi_strlen(line);
        if (len > longest) longest = len;
    }
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        int to_add = longest - ansi_strlen(vec.at(i));
        if (!to_add) continue;
        int add_front = to_add / 2;
        int add_back = to_add - add_front;
        vec.at(i) = string(add_front, ' ') + vec.at(i) + string(add_back, ' ');
    }
    return longest;
}

// String split/explode function, handles ANSI colour tags.
vector<string> ansi_string_explode(const string& str, unsigned int line_len)
{
    vector<string> output;

    // Check to see if the line of text has the no-split tag at the start.
    if (str.size() >= 3)
    {
        if (!str.substr(0, 3).compare("{_}"))
        {
            output.push_back(str.substr(3));
            return output;
        }
    }

    // Check to see if the line is too short to be worth splitting.
    if (ansi_strlen(str) <= line_len)
    {
        output.push_back(str);
        return output;
    }

    // Split the string into individual words.
    vector<string> words = string_explode(str, " ");

    // Keep track of the current line and our position on it.
    unsigned int current_line = 0, line_pos = 0;
    string last_colour = "{0}";    // The last colour tag we encountered; ANSI reset code by default.

    // Start with an empty string.
    output.push_back("");

    for (auto word : words)
    {
        unsigned int length = ansi_strlen(word);    // Find the length of the word, without ANSI tags.

        if (length + line_pos >= line_len)  // Is the word too long for the current line?
        {
            line_pos = 0; current_line++;   // CR;LF
            if (last_colour != "{0}") output.push_back(last_colour);    // Start the line with the last colour tag we saw, if any.
            else output.push_back("");
        }
        size_t open_tag = word.find_last_of('{'), close_tag;
        if (open_tag != string::npos)
        {
            // Duplicate the last-used colour tag.
            close_tag = word.find_last_of('}');
            if (close_tag != string::npos) last_colour = word.substr(open_tag, (close_tag - open_tag + 1));
        }
        if (line_pos != 0)  // NOT the start of a new line?
        {
            length++;
            output.at(current_line) += " ";
        }

        // Is the word STILL too long to fit over a single line?
        while (length > line_len)
        {
            const string trunc = word.substr(0, line_len);
            word = word.substr(line_len);
            output.at(current_line) += trunc;
            line_pos = 0;
            current_line++;
            output.push_back(last_colour);  // Start the line with the last colour tag we saw.
            length = word.size();   // Adjusts the length for what we have left over.
        }
        output.at(current_line) += word;
        line_pos += length;
    }

    return output;
}

// Strips all ANSI colour tags like {M} from a string.
string ansi_strip(const string& str)
{
    string result = str;
    while(true)
    {
        size_t found_open = result.find_first_of('{');
        size_t found_closed = result.find_first_of('}', found_open);
        if (found_open == string::npos || found_closed == string::npos) return result;
        result = result.substr(0, found_open) + result.substr(found_closed + 1);
    }
}

// Returns the length of a specified string, not counting the ANSI colour tags like {G} or {kR}.
size_t ansi_strlen(const string &str)
{ return ansi_strip(str).length(); }

// Splits an ANSI-tagged string across multiple lines of text.
vector<string> ansi_vector_split(const string& str, uint32_t line_length)
{
    string current_line, last_tag;
    vector<string> result, words = text::manipulation::string_explode(str, " ");
    uint32_t current_pos = 0;

    while(words.size())
    {
        string word = words.at(0);
        words.erase(words.begin());

        // Determine if any ANSI tags are within this word. If so, record the last tag. Then measure the word length.
        size_t found_open = word.find_last_of('{');
        size_t found_closed = word.find_first_of('}', found_open);
        size_t word_len = 0;
        if (found_open != string::npos && found_closed != string::npos)
        {
            last_tag = word.substr(found_open, found_closed - found_open + 1);
            word_len = ansi_strlen(word);
        }
        else word_len = word.size();

        // Decide whether or not we're starting a new line.
        if (current_pos && (current_pos + word_len >= line_length))
        {
            result.push_back(current_line);
            current_line = last_tag + word;
            current_pos = word_len + 1;
        }
        else
        {
            current_line += (current_pos  ? " " : "") + word;
            current_pos += word_len + 1;
        }
    }
    if (current_line.size()) result.push_back(current_line);
    return result;
}

// Counts all the colour tags in a string.
size_t count_colour_tags(const string& str)
{
    size_t tags = 0;
    for (size_t i = 0; i < str.size(); i++)
        if ((str.at(i) == '{') && ((str.size() > i + 1 && str.at(i + 1) == '}') || (str.size() > i + 2 && str.at(i + 2) == '}'))) tags++;
    return tags;
}

// 'Flattens' ANSI tags, by erasing redundant tags in the string.
string flatten_tags(const string& str)
{
    string output, to_check = str, last_tag;

    while(true)
    {
        size_t tag_open = to_check.find_first_of('{');
        size_t tag_closed = to_check.find_first_of('}', tag_open);
        if (tag_open == string::npos || tag_closed == string::npos)
        {
            output += to_check;
            break;
        }
        string tag_found = to_check.substr(tag_open + 1, tag_closed - tag_open - 1);
        if (tag_found.compare(last_tag))
        {
            last_tag = tag_found;
            output += to_check.substr(0, tag_closed + 1);
        }
        else output += to_check.substr(0, tag_open);
        to_check = to_check.substr(tag_closed + 1);
    }

    return output;
}

// Generates a bar of the specified type.
string generate_bar(BarType type, float num, float num_max, int width)
{
    string result, l_cap, r_cap, bar_col, empty_col;
    char bar_glyph = '?', empty_glyph = '?';
    float percentage = num / num_max;

    switch (type)
    {
        case BarType::PROGRESS: l_cap = "{W}["; r_cap = "{W}]"; bar_col = "{G}"; empty_col = "{B}"; bar_glyph = '/'; empty_glyph = '.'; break;
        default: throw runtime_error("Unknown bar type on generate_bar: " + std::to_string(static_cast<int>(type)));
    }
    int total_glyphs = width;
    if (l_cap.size()) total_glyphs -= ansi_strlen(l_cap);
    if (r_cap.size()) total_glyphs -= ansi_strlen(r_cap);
    int bar_glyphs = std::round(static_cast<float>(total_glyphs) * percentage);

    if (bar_glyphs) result = bar_col + string(bar_glyphs, bar_glyph) + empty_col + string(total_glyphs - bar_glyphs, empty_glyph);
    else result = string(total_glyphs, empty_glyph);

    return l_cap + result + r_cap;
}

// Makes pretty rainbow text!
string rainbow_text(const string& str, const string& colours)
{
    string output;
    int position = 0;
    int direction = 5;

    for (auto letter : str)
    {
        output += colours.substr(position, 5) + string(1, letter);
        position += direction;
        if (position >= static_cast<int>(colours.size())) { position -= 10; direction = -5; }
        else if (position < 0) { position = 5; direction = 5; }
    }

    return output;
}

// Similar to string_explode(), but takes colour tags into account, and wraps to a given line length.
vector<string> string_explode_colour(const string& str, unsigned int line_len, const string& default_colour)
{
    vector<string> output;
    if (!str.size()) return output;

    // Check to see if the line is too short to be worth splitting.
    if (ansi_strlen(str) <= line_len)
    {
        output.push_back(str);
        return output;
    }

    // Split the string into individual words.
    vector<string> words = string_explode(str, " ");

    // Keep track of the current line and our position on it.
    unsigned int current_line = 0, line_pos = 0;
    string last_colour = default_colour;    // The last colour tag we encountered; white by default.

    // Start with an empty string.
    output.push_back("");

    for (auto word : words)
    {
        unsigned int length = word.length();    // Find the length of the word.

        const int colour_count = word_count(word, "{"); // Count the colour tags.
        if (colour_count) length -= (colour_count * 3); // Reduce the length if one or more colour tags are found.
        if (length + line_pos >= line_len)  // Is the word too long for the current line?
        {
            line_pos = 0; current_line++;   // CR;LF
            output.push_back(last_colour);  // Start the line with the last colour tag we saw.
        }
        if (colour_count)
        {
            // Duplicate the last-used colour tag.
            const string::size_type flo = word.find_last_of("{");
            if (flo != string::npos && word.size() >= flo + 3) last_colour = word.substr(flo, 3);
        }
        if (line_pos != 0)  // NOT the start of a new line?
        {
            length++;
            output.at(current_line) += " ";
        }

        // Is the word STILL too long to fit over a single line?
        while (length > line_len)
        {
            const string trunc = word.substr(0, line_len);
            word = word.substr(line_len);
            output.at(current_line) += trunc;
            line_pos = 0;
            current_line++;
            output.push_back(last_colour);  // Start the line with the last colour tag we saw.
            length = word.size();   // Adjusts the length for what we have left over.
        }
        output.at(current_line) += word;
        line_pos += length;
    }

    if (output.size() && output.at(0)[0] != '{') output.at(0) = default_colour + output.at(0);
    return output;
}

}   // namespace trailmix::text::amsi
