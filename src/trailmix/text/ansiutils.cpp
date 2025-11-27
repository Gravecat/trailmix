// text/ansiutils.cpp -- Various utility functions that deal with string manipulation/conversion -- in particular, strings that use a special type of tags I use in my own projects
// for marking where ANSI colour codes will be inserted into text.

#include "trailmix/text/ansiutils.hpp"
#include "trailmix/text/stringutils.hpp"

using std::string;
using std::vector;

namespace trailmix {

// Strips all ANSI colour tags like {M} from a string.
string ansi_strip(const string &str)
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
vector<string> ansi_vector_split(const string &str, uint32_t line_length)
{
    string current_line, last_tag;
    vector<string> result, words = stringutils::string_explode(str, " ");
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

// 'Flattens' ANSI tags, by erasing redundant tags in the string.
string flatten_tags(const string &str)
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

}   // namespace trailmix
