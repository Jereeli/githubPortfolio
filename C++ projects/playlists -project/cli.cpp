#include "cli.hh"
#include "utilities.hh"

#include <algorithm>
#include <iostream>

using namespace std;

Cli::Cli(shared_ptr<Music> db) :
    database_(db)
{

}

bool Cli::exec_prompt()
{
    // Query for the command, and split input
    string line;
    cout << PROMPT;
    getline(cin, line);

    vector<string> args = Utilities::split(line, ' ', false);

    // Empty input, do nothing
    if (args.size() == 0) {
        return false;
    }

    // Get command type, check parameter amount and execute command
    auto command = check_command_type(args);

    // Separate parameters from the base command
    vector<string> params(args.begin()+1, args.end());

    // If the command needs a specified amount of parameters and the amount is
    // not correct, print an error and stop
    if (command.params_n != ANY_N_PARAMS and
        params.size() != static_cast<unsigned long>(command.params_n))
    {
        print_error(Error::WRONG_N_PARAMS);
        return false;
    }

    if (command.func != nullptr) {
        command.func(params);
    }

    return command.ends_execution;
}

CommandInfo Cli::check_command_type(vector<string> const& args) {
    // Remove the case sensitivity
    string base = args[0];
    transform(base.begin(), base.end(),base.begin(), ::tolower);

    auto cmd_iter = find_if(COMMANDS.begin(), COMMANDS.end(), [base] (CommandInfo cmd) {
        return cmd.name == base;
    });

    // Point to unknown command if no match was found.
    if (cmd_iter == COMMANDS.end()) {
        return UNKNOWN_COMMAND;
    }

    // Dereference iterator.
    return *cmd_iter;
}

void Cli::print_error(Error error_type)
{
    switch (error_type) {
    case Error::UNKNOWN_COMMAND:
        cout << "Error: unkown command." << endl;
        break;
    case Error::WRONG_N_PARAMS:
        cout << "Error: wrong amount of parameters." << endl;
        break;
    }
}
