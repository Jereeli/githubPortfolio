/* Playlists
 *
 * Intro:
 *
 * Implementation of functions in file music. Contains the
 * implemations of Playlists classes methods and Music classes
 * methods
 *
 * Developer
 * Name: Jeremia Haapasalmi
 * Student ID: 152127352
 * Git username: fkjeha
 * E-Mail: jeremia.haapasalmi@tuni.fi
 *
 * */


#include "music.hh"
#include "utilities.hh"

#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <random>


using namespace std;

Playlist::Playlist()
{

}

Playlist::Playlist(std::string name, std::string creator, std::vector<std::shared_ptr<Song>> songs):
    name_(name), creator_(creator), songs_(songs)
{
}


string Playlist::getName(){
    return name_;
}

string Playlist::getCreator(){
    return creator_;
}

vector<std::shared_ptr<Song>> Playlist::getSongs(){
    return songs_;
}

void Playlist::print_songs(){

    int total_time = 0;
    int i = 1;

    cout << name_ << ", created by " << creator_ << endl;

    for(auto it = songs_.begin(); it != songs_.end(); ++it)
    {
        total_time += (*it)->duration;

        cout << "  " << i << ". " << (*it)->artist << " - " << (*it)->song_name <<
            " (" << Utilities::time_to_string((*it)->duration) << ")" << endl;
        i++;
    }

    cout << "Total duration " << Utilities::time_to_string(total_time) << endl;
}


Music::Music()
{
}


bool Music::read_from_file(std::string file_name)
{
    bool playlist = false;
    const vector<string> ERRORS = {"Error: incorrect row in file.",
                                    "Error: could not open file.", "Error: song not found."};

    vector<shared_ptr<Song>> songs_to_add;       
    string row;
    string id; string song_name; string artist; string duration;
    string playlist_name; string creator;

    ifstream file(file_name);

    string new_artist;
    string new_song_name;
    int new_duration;

    string new_playlist_name;
    string new_creator;

    if(!file){
        cout << ERRORS.at(1);
        return false;
    }

    while( getline( file, row ) )
    {
        if(row.empty())
        {continue;}

        else
        {
            vector<string> data = Utilities::split(row, ';', false);

            if(data.at(0) == "PLAYLISTS")
            {
                // Checks if word PLAYLIST has appeared in file
                playlist = true;
                continue;
            }

            else if(data.size() != 4 && !playlist){
                cout << ERRORS.at(0);
                return false;
            }
            else if(!playlist){
                shared_ptr<Song> new_song = make_shared<Song>(); // Smart pointer to struct Song
                
                new_artist = data.at(1);
                new_song_name = data.at(2);

                if( Utilities::is_int(data.at(3)) ){
                    new_duration = stoi(data.at(3));
                }
                else{
                    cout << ERRORS.at(0);
                    return false;
                }

                // Parameters to create Song object from
                new_song->artist = new_artist;
                new_song->song_name = new_song_name;
                new_song->duration = new_duration;

                songs_[data.at(0)] = new_song;
                songs_vector_.push_back(*new_song); // Used for sorting songs by alphabetical order
            }
            else if(data.size() != 3 && playlist){
                cout << ERRORS.at(0);
                return false;
            }
            else if(playlist)
            {
                // After PLAYLIST row in file:
                vector<string> data = Utilities::split(row, ';', false);
                vector<string> songs_vector = Utilities::split(data.at(2), '|', false); // Song names

                for( string i : songs_vector ){
                    // Save each new song in a vector
                    auto it = songs_.find(i);
                    if( it != songs_.end()){
                        songs_to_add.push_back(it->second);
                    }
                    else{
                        cout << ERRORS.at(2);
                        return false;
                    }
                }

                new_playlist_name = data.at(0);
                new_creator = data.at(1);

                Playlist new_playlist(new_playlist_name, new_creator, songs_to_add);

                // Create key with name of the playlist and value class Playlist
                playlists_[new_playlist_name] = new_playlist;

                songs_to_add.clear();
                }
                }
            
            }
            return true;
        }



void Music::playlists_command()
{
    for( auto it = playlists_.begin(); it != playlists_.end(); ++it){
        cout << it->second.getName() << ',' << " created by " << it->second.getCreator() << endl;
    }
}

void Music::playlist_command(std::string name)
{

    for( auto it = playlists_.begin(); it != playlists_.end(); ++it){
        if(name == it->first){
            it->second.print_songs();
            return;
        }
    }
    cout << "Error: playlist not found." << endl;
}

void Music::songs_command()
{
    // Sort the songs_vector to be in alphabetical order
    std::sort(songs_vector_.begin(), songs_vector_.end(),
        [](const Song& a, const Song& b) {
            if (a.artist != b.artist) {
                return a.artist < b.artist;
            }
            return a.song_name < b.song_name;
            }
        );
    for( auto it = songs_vector_.begin(); it != songs_vector_.end(); ++it ) {
        cout << it->artist << " - " << it->song_name << " (" <<
            Utilities::time_to_string(it->duration) << ")" << endl;
    }
}


void Music::favorites_command(std::string user)
{
    map<string, int> artist_counts;

    // Go through each playlist in class playlist
    for (const auto& pair : playlists_) {
        Playlist pl = pair.second;

        // If the list is made by given user
        if (pl.getCreator() == user) {
            // Go through each song
            for (const auto& song_ptr : pl.getSongs()) {
                if (song_ptr != nullptr) { // avoid errors
                    artist_counts[song_ptr->artist]++; // increase the count of artist, if not yet in map, add it
                }
            }
        }
    }

    int max_count = 0;
    for (const auto& pair : artist_counts) {
        // Go through each artists count in map
        if (pair.second > max_count) {
            // If artists count exceeds the current max count, save it as max count
            max_count = pair.second;
        }
    }

    cout << "Favorite artist(s) of " << user << " (appeared " << max_count
         << " times):" << endl;

    for(const auto& pair : artist_counts) {
        // Print each artist that has counts equal to highest counts
        if (pair.second == max_count) {
            cout << "  " << pair.first << endl;
        }
    }
}

void Music::shuffle_command(const std::string& name, std::string seed)
{
    Playlist* target_playlist = nullptr;

    for (auto& pair : playlists_) {
        if (pair.second.getName() == name) {
            target_playlist = &pair.second; // Save the playlist
            break;
        }
    }

    // If not found
    if (target_playlist == nullptr) {
        cout << "Error: playlist not found." << endl;
        return;
    }

    // If seed is not a number
    if( !Utilities::is_int(seed) ) {
        cout << "Error: incorrect seed parameter." << endl;
        return;
    }

    int seed_int = stoi(seed);

    // Create a new vector that c
    vector<std::shared_ptr<Song>> temp_songs = target_playlist->getSongs();


    std::default_random_engine random(seed_int);

    std::shuffle(temp_songs.begin(), temp_songs.end(), random);

    cout << target_playlist->getName() << ", created by " << target_playlist->getCreator() << endl;

    int i = 1;
    int total_time = 0;

    for (const auto& song_ptr : temp_songs) {
        total_time += (*song_ptr).duration;
        if (song_ptr) {
            cout << "  " << i << ". " << song_ptr->artist << " - " << song_ptr->song_name
                      << " (" << Utilities::time_to_string(song_ptr->duration) << ")" << std::endl;
        }
        i++;
    }
    cout << "Total duration " << Utilities::time_to_string(total_time) << endl;
}
