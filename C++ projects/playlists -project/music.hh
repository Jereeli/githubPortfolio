/* Playlists
 *
 * Intro:
 *
 * Header file of classes Playlist and Music. Introduces each method and paramters
 * they need.
 *
 * Developer
 * Name: Jeremia Haapasalmi
 * Student ID: 152127352
 * Git username: fkjeha
 * E-Mail: jeremia.haapasalmi@tuni.fi
 *
 * */


#ifndef MUSIC_HH
#define MUSIC_HH


#include <string> 
#include <map>
#include <vector>
#include <memory>

/*
Struct that contains information that a song can store
 */

struct Song 
{
    std::string artist;
    std::string song_name;
    int duration;
};

/*
Struct that contains information that playlist can store
*/

class Playlist
/*
 * Class that holds playlists attributes and methods
 *
 */
{
public:

    // Constructors
    Playlist();
    Playlist(std::string name, std::string creator, std::vector<std::shared_ptr<Song>> songs_to_add);

    // Getter methods:
    std::string getName();

    std::string getCreator();

    std::vector<std::shared_ptr<Song>> getSongs();

    /**
     * @brief Prints each song in playlist in alphabetical order
     */
    void print_songs();

    /**
     * @brief shuffle_command Shuffles the given playlist's song order and
     *   prints the new order. Does not actually modify the original
     *   playlist however.
     * @param name The name of the playlist.
     * @param seed The seed to use in the rng.
     */


private:
// Playlist object has name, creator of playlist and pointers to songs
    std::string name_;
    std::string creator_;
    std::vector<std::shared_ptr<Song>> songs_;
};

class Music
{
public:
    Music();

    /**
     * @brief read_from_file Reads song and playlist information into the
     *   from an input file.
     * @param file_name The name of the file to read.
     * @return true if the read was completely successful, false if an
     *   error occurred during reading of the file.
     */
    bool read_from_file(std::string file_name);


    /**
     * @brief playlists_command Prints all playlists saved in this program
     *   in alphabetical order of the playlist names.
     */
    void playlists_command();

    void playlist_command(std::string name);
    /**
     * @brief songs_command Prints all songs in the program in alphabetical order
     * first by artist name and then by song name.
     */
    void songs_command();

    /**
     * @brief favorites_command Prints the given user's favorite artist(s), AKA.
     *   the artist(s) whose songs appear the most times in the user's playlists.
     *   Also print the amount of times their songs are featured.
     * @param user The name of the user.
     */
    void favorites_command(std::string user);


    /**
     * @brief Prints given playlist in a completely randomized order. (Does not affect
     * the original playlist
     * @param name The name of the playlist to be shuffled
     * @param seed Seed to be used in random number generator
     */
    void shuffle_command(const std::string& name, std::string seed);

private:
    // Add private attributes and functions

    std::map<std::string, Playlist> playlists_;
    std::map<std::string, std::shared_ptr<Song>> songs_;
    std::vector<Song> songs_vector_;
};

#endif // MUSIC_HH
