////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

sf::TcpSocket NLS::Network::Socket;

void NLS::Network::Init() {
	if (Socket.Connect("127.0.0.1", 8484, 2000) != sf::Socket::Done) {
		ucerr << U("Failed to connect to server at ") << ustring(Socket.GetRemoteAddress().ToString()) << endl;
	} else {
		ucout << U("Connected to LoginServer at ") << ustring(Socket.GetRemoteAddress().ToString())  << endl;
	}
}