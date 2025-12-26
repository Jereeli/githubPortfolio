#include "Utilities.h"

#include <iostream>
#include <vector>
#include <windows.h>
#include <clocale>

using namespace std;



int main()
{
    std::setlocale(LC_ALL, "Finnish");


    string filename;
    string command;
    vector<string> wordle;

    cout << " --------WORDLE-------- ";
    cout << "\n\n\n";

    while( wordle.empty() ) {
        cout << "Aloita syöttämällä tiedostonimi: ";
        getline(cin, filename);
        wordle = Utilities::fileToWordle(filename);
    }

    cout << " --------KOMENNOT-------- " << endl;
    cout << " - /peli: Uusi peli" << endl;
    cout << " - /sana: Uusi sana" << endl;
    cout << " - /help: Ohjeet" << endl;
    cout << " - /quit: Lopeta peli\n" << endl;

    while( command != "/quit" ) {

        cout << "> ";
        getline(cin, command);


        if( command == "/peli" ) {
           if( !Utilities::playWordle(wordle) ) {
            command = "/quit";
           }
        }


    }

    return EXIT_SUCCESS;
}
