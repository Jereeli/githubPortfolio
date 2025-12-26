#ifndef UTILITIES_HH
#define UTILITIES_HH

#include <vector>
#include <string>

namespace Utilities {

// Splits the given string into parts by a given delimiter and stores them
// into a vector. If keep_empty is false, the function doesn't store empty parts.
std::vector<std::string> split(const std::string& str, char delim, bool keep_empty = false);

// Checks if the given string is an integer, and consists only of digits.
// If allow_negative is true, the string can additionally have a '-' prefix.
bool is_int(std::string str, bool allow_negative = false);


// Converts given seconds into 00:00 -time format.
// Takes int as a parameter and returns string.
std::string time_to_string(int seconds);


#endif // UTILITIES_HH
}
