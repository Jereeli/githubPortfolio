#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include <string>

namespace Utilities{

    /**
        @brief Splits line

        Splits given line into individual words
        @param string line Line as a string to be separated
        @param char separator Character, which  separates the words
        @return vector<string> Individual words in a vector
    */
    std::vector<std::string> split(const std::string& line, char separator);

    /**
        @brief Forms wordle dictionary from given file

        @param string filename Name of the file
        @return vector<string> wordle words in vector
    */
    std::vector<std::string> fileToWordle(const std::string filename);

    /**
        @brief Returns random word from a vector

        @param vector<string> words Vector of words
        @return string Random word from given vector
    */
    std::string randomWord(const std::vector<std::string>& words);

    bool playWordle(const std::vector<std::string>& words);

}

#endif // UTILITIES_H
