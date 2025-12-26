/*
#############################################################################
# COMP.CS.110 Ohjelmointi 2: Tekniikat / Programming 2: Techniques          #
# Project: Playlists / Soittolistat                                         #
# File: cli.hh                                                              #
# Description: Commandline interface for the program.                       #
# Notes: * This is a part of an exercise program.                           #
#        * Student's don't touch this file.                                 #
#        * Understanding how the module works isn't necessary to complete   #
#          this exercise.                                                   #
#        * This could be upgraded to have a command history with relative   #
#          ease.                                                            #
#############################################################################
*/

#ifndef CLI_HH
#define CLI_HH

#include "music.hh"

#include <string>
#include <vector>
#include <memory>
#include <functional>

enum class Error {
    UNKNOWN_COMMAND,
    WRONG_N_PARAMS
};

using Command = std::function<void(std::vector<std::string>)>;

// CommandInfo contains the string that selects it, command settings
// (amount of parameters, and if it ends execution) and a function
// to be executed if the command is a match.
struct CommandInfo
{
    std::string name;
    int params_n;
    bool ends_execution;
    Command func;
};
const int ANY_N_PARAMS = -1;

const std::string PROMPT = "cmd> ";

class Cli
{
public:
    // The database that is going to be used is given as a parameter.
    Cli(std::shared_ptr<Music> db);

    /* Description: Runs the interface.
     * Return values:
     *  True    - Normal command
     *  False   - Exit command
     */
    bool exec_prompt();

private:
    std::shared_ptr<Music> database_;

    const CommandInfo UNKNOWN_COMMAND = {"", ANY_N_PARAMS, false, [this] (auto) {print_error(Error::UNKNOWN_COMMAND);}};

    // Constant table that contains the different commands that the CLI can
    // recognize.
    const std::vector<CommandInfo> COMMANDS {
        {"quit", 0, true, nullptr},
        {"playlists", 0, false, [this] (auto) {database_->playlists_command();}},
        {"playlist", 1, false, [this] (auto params) {database_->playlist_command(params.at(0));}},
        {"songs", 0, false, [this] (auto) {database_->songs_command();}},
        {"favorites", 1, false, [this] (auto params) {database_->favorites_command(params.at(0));}},
        {"shuffle", 2, false, [this] (auto params) {database_->shuffle_command(params.at(0), params.at(1));}}
    };

    CommandInfo check_command_type(const std::vector<std::string> &args);
    void print_error(Error error_type);
};

#endif // CLI_HH
