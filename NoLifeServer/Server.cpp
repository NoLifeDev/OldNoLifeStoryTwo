///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

NLS::LoginServer* loginServer;

void NLS::Init(vector<string> args) {
	loginServer = new LoginServer();
	//for each world
	//do the same with a WorldServer
	//plus for each channel in that world
	//do the same with a ChannelServer
}

bool NLS::Loop() {
	char s[1024];
	cin.getline(s, 1024);
	string command = s;
	//Do stuff with the command
	return true;
}

void NLS::Unload() {

}