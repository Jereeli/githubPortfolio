#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <windows.h>
#include <utility>
#include <map>
#include <algorithm>
#include <set>


namespace Utilities {

    std::vector<std::string> split(const std::string& line, char separator)
    {
        std::vector<std::string> words;
        std::string::size_type start = 0;
        std::string::size_type tempEnd;


        while ((tempEnd = line.find(separator, start)) != std::string::npos)
        {

            std::string word = line.substr(start, tempEnd - start);

            if (!word.empty()) {
                words.push_back(word);
            }

            start = tempEnd + 1;
        }

        std::string lastWord = line.substr(start);
        if (!lastWord.empty()) {
            words.push_back(lastWord);
        }

        return words;
    }

    std::vector<std::string> fileToWordle(const std::string filename) {

        std::vector<std::string> wordleDictionary;
        std::vector<std::string> wordRow;
        std::ifstream file(filename);
        std::string row;

        if( !file.is_open() ) {
            std::cerr << "Virhe tiedostoa avattaessa. Tarkista syöttämäsi tiedosto.\n\n";
            return wordleDictionary;
        }

        while( std::getline(file, row) ) {
            if( !row.empty() ) {
                wordRow = split(row, ';');
                for( std::string row : wordRow ) {
                 wordleDictionary.push_back(row);
                }
            }
        }
        std::cout << "Wordle sanat päivitetty onnistuneesti.\n\n";
        return wordleDictionary;
    }

    std::string randomWord(const std::vector<std::string>& words) {

        std::size_t wordAmount = words.size();
        std::string output;

        std::random_device seed;
        std::mt19937 gen(seed()); // Creates a random seed for random number generation

        std::uniform_int_distribution<> dis(0, wordAmount - 1);

        int randomIndex = dis(gen);

        return words.at(randomIndex);
    }

     bool playWordle(const std::vector<std::string>& words) {

        std::string correctWord = randomWord(words);

        std::map<std::size_t, std::string> correctChars;
        std::set<char> guessedChars;
        std::string output;
        int guesses = 1;

        std::vector<std::string> COMMANDS = {"/peli", "/sana",
                                                "/help", "/quit"};
         std::cout << "Aloita arvaamalla " << correctWord.size() << " kirjainta "
                    << "pitkä sana." << std::endl;

        while( true ) {

            std::cout << "\n> ";
            getline(std::cin, output);

            if( output.at(0) == '/' ) {
                auto it = std::find(COMMANDS.begin(), COMMANDS.end(), output);
                if ( it == COMMANDS.end() ) {
                    std::cout << "Komentoa ei tunnistettu. Kirjoita /help saadaksesi ohjeet." << std::endl;
                }
                else if ( output == "/peli" ) {
                    std::cout << "Peli on jo käynnissä." << std::endl;
                }
                else if ( output == "/sana" ) {
                    guessedChars.clear();
                    correctChars.clear();
                    guesses = 0;
                    correctWord = randomWord(words);
                    std::cout << "Uusi sana valittu. Aloita arvaamalla " << correctWord.size() << " kirjainta"
                    << "pitkä sana." << std::endl;

                }
                else if ( output == "/help" ) {
                    std::cout << "Tehtävänäsi on arvata satunnaisesti valittu suomenkielinen sana."
                        << " Jokainen arvattu sana antaa sinulle vihjeitä sen mukaan, että oliko "
                        << "sanassasi jokin kirjaimista oikealla paikalla, tai oliko arvauksessasi oikeita"
                        << "kirjaimia, mutta väärillä paikoilla.\n" << std::endl;

                    std::cout << " --------KOMENNOT-------- " << std::endl;
                    std::cout << " - /peli: Uusi peli" << std::endl;
                    std::cout << " - /sana: Uusi sana" << std::endl;
                    std::cout << " - /help: Ohjeet" << std::endl;
                    std::cout << " - /quit: Lopeta peli\n" << std::endl;
                }
                else if ( output == "/quit" ) {
                    return false;
                }
            }

            else if( output.size() != correctWord.size() ) {
                std::cout << "Arvatun sanan pituus on väärä. Oikea sana on " << correctWord.size()
                << " kirjainta pitkä." << std::endl;
            }

            else {
                guessedChars.clear();

                for( size_t i = 0; i < output.length(); i++ ) {
                    char c = output[i];

                    if( c == correctWord[i] ) {
                        correctChars[i] = c;
                    }
                    else if( correctWord.find(c) != std::string::npos) {
                        guessedChars.insert(c);
                    }
                }

                std::cout << "Arvauksia käytetty: " << guesses << std::endl;
                //Print currently revealed word:
                for(size_t i = 0; i < correctWord.length(); i++ ) {
                    auto it = correctChars.find(i);
                    if( it != correctChars.end() ) {
                        std::cout << it->second;
                    }
                    else {
                        std::cout << "_ ";
                    }
                }

                //Print correct characters
                if( guessedChars.size() > 0 ) {

                std::cout << " (Arvaamassasi sanassa \"" << output << "\" nämä kirjaimet ovat väärillä paikoilla: ";
                for( char letter : guessedChars ) {
                    std::cout << letter << " ";
                }

                std::cout << ")";
                }

                if( correctChars.size() == correctWord.size() ) {
                    std::cout << "\nOikein! Arvasit sanan " << correctWord << " " << guesses << " yrityksellä!" << std::endl;
                    return true;
                }
                std::cout << std::endl;
                guesses++;
            }
     }
    }

}
