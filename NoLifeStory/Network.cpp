////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

sf::TcpSocket NLS::Network::Socket;

void NLS::Network::Init() {
	if (Socket.Connect("localhost", 10273) != sf::Socket::Done) {
		cerr << "ERROR: Failed to connect to server" << endl;
	}
}