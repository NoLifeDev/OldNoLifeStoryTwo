///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

NLS::LoginServer* loginServer;

void NLS::Init(vector<string> args) {
	LoginServer::Start();
	WorldServer::Start();
	cout << "INFO: NoLifeServer is up and running" << endl;
}

void NLS::Loop() {
	auto GetCommand = []()->vector<string>{
		string command;
		char cstr[1024];
		cin.getline(cstr,1024);
		command = cstr;
		istringstream iss(command);
		vector<string> words;
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string>>(words));
		return words;
	};
	while (true) {
		vector<string> command = GetCommand();
		if (command.size() == 0) {
			continue;
		} else if (command[0] == "help" or command[0] == "?") {
			if (command.size() > 1) {
				if (command[1] == "shutdown") {
					cout << "HELP: Shuts down NoLifeServer gracefully, preserving all data" << endl;
				} else if (command[1] == "forceshutdown") {
					cout << "HELP: Forces NoLifeServer to shutdown immediately, losing any temporary data" << endl;
				} else if (command[1] == "help" or command[1] == "?") {
					cout << "HELP: Displays information on commands available and what each command does" << endl;
				}
			} else {
				cout << "HELP: Available commands: help, ?, shutdown, forceshutdown" << endl;
				cout << "HELP: Enter \"help command\" for help with a particular command" << endl;
			}
		} else if (command[0] == "shutdown") {
			return;
		} else if (command[0] == "forceshutdown") {
			cout << "INFO: Forcing NoLifeServer shutdown" << endl;
			exit(1);
		} else {
			cout << "INFO: Unknown command: " << command[0] << endl;
		}
	}
	return;
}

void NLS::Unload() {
	cout << "INFO: Initiating NoLifeServer shutdown" << endl;
	LoginServer::Shutdown();
	WorldServer::Shutdown();
	cout << "INFO: NoLifeServer shutdown complete" << endl;
	system("pause");
}