/* Playlists
 *
 * Intro:
 *
 * Main function of program that processes info about songs
 * and  playlists from a user's given file.
 * The program is able to create new playlists, with songs in in, and store
 * information about the songs and the creator of the playlist for example.
 *
 * Songs in file to read must be in a form, where each row is written as:
 *  ID;Artist;song name; duration in seconds
 * Playlists must be written in form:
 *  Name;creator;ID of song 1|ID of song 2| etc...
 * Info rows from songs and albums must be seperated with a row:
 * PLAYLISTS
 *
 * The songs are stored in a vector, where each album has a smart pointer
 * to, so that duplicates can't occur. Playlists are made with class objects,
 * and interactions are made possible with methods.
 * methods

 * Developer
 * Name: Jeremia Haapasalmi
 * Student ID: 152127352
 * Git username: fkjeha
 * E-Mail: jeremia.haapasalmi@tuni.fi
 *
 * */

#include "cli.hh"
#include "music.hh"

#include <iostream>
#include <memory>

using namespace std;

int main() {

    shared_ptr<Music> music_db = make_shared<Music>();

    cout << "Input file: ";
    string input_file;
    getline(cin, input_file);
    if (!music_db->read_from_file(input_file)) {
        return EXIT_FAILURE;
    }
    cout << endl;

    shared_ptr<Cli> cli = make_shared<Cli>(music_db);

    bool exit_program = false;
    while (!exit_program) {
        exit_program = cli->exec_prompt();

        if (!exit_program) {
            cout << endl;
        }
    }

    return EXIT_SUCCESS;
}
