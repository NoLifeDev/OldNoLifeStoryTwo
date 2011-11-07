////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

sf::TcpSocket NLS::Network::Socket;

void NLS::Network::Init() {
	if (Socket.Connect("127.0.0.1", 8484, 2000) != sf::Socket::Done) {
		cerr << "Failed to connect to server at " << string(Socket.GetRemoteAddress().ToString()) << endl;
	} else {
		cout << "Connected to LoginServer at " << string(Socket.GetRemoteAddress().ToString())  << endl;
	}
}