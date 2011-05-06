///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

sf::TcpListener Listener;
sf::TcpSocket* NextSocket;

void NLS::Init(vector<string> args) {
	Listener.Listen(10273);
	Listener.SetBlocking(false);
	NextSocket = new sf::TcpSocket;
}

bool NLS::Loop() {
	if (Listener.Accept(*NextSocket)) {
		new Connection(NextSocket);
		NextSocket = new sf::TcpSocket;
	}
	//Other server stuff
	//Everything happens here
	return true;
}

void NLS::Unload() {

}