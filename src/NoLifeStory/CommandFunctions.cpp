////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

CommandListType CommandFunctions::CommandList;

void CommandFunctions::initialize() {
	// Set up commands
	Command command;

	// Notes:
	// Don't add syntax to things that have no parameters
	// Every command needs at least one line of notes that describes what the command does

	command.command = &Functions::help;
	command.syntax = "[$command]";
	command.notes.push_back("I wonder what it does?");
	command.notes.push_back("Syntax for help display:");
	command.notes.push_back("$ = string");
	command.notes.push_back("# = number");
	command.notes.push_back("${hi | bye} = specific choices, in this case, strings of hi or bye");
	command.notes.push_back("<#time in seconds> = required parameter");
	command.notes.push_back("[#time in seconds] = optional parameter");
	CommandList["help"] = command.addToMap();
}

bool CommandFunctions::runRegexPattern(const string &args, const string &pattern, cmatch &matches) {
	regex re;
	re = pattern; // An implicit conversion that C++ refuses to do otherwise
	// Compiles matches if successful and will return true
	// Otherwise returns false
	return regex_match(args.c_str(), matches, re);
}

void CommandFunctions::showSyntax(const string &command, bool fromHelp) {
	if (CommandList.find(command) != CommandList.end()) {
		Command &cmd = CommandList[command];

		NLS::C("INFO") << "Usage: !" << command << " " << cmd.syntax << endl;
		if (fromHelp) {
			NLS::C("INFO") << cmd.notes[0] << endl;
			for (size_t i = 1; i < cmd.notes.size(); i++) {
				NLS::C("INFO") << cmd.notes[i] << endl;
			}
		}
	}
}

bool CommandFunctions::handleCommand(const string &command, const string &args) {
	if (CommandList.find(command) == CommandList.end()) {
		NLS::C("INFO") << "Command \"" << command << "\" does not exist." << endl;
		return false;
	}
	else {
		Command &cmd = CommandList[command];
		if (!cmd.command(args)) {
			CommandFunctions::showSyntax(command);
		}
	}
	return true;
}