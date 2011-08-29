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
	if (Listener.Accept(*NextSocket) == sf::Socket::Done) {
		cout << "Connection from " << NextSocket->GetRemoteAddress() << ":" << NextSocket->GetRemotePort() << endl;
		new Connection(NextSocket);
		NextSocket = new sf::TcpSocket;
	}
	stack<Connection*> towipe;
	for (auto it = Connections.begin(); it != Connections.end(); it++) {
		Connection* c = *it;
		sf::Packet p;
		auto s = c->socket->Receive(p);
		switch (s) {
		case sf::Socket::Error:
			cout << "Error receiving packet from " << c->socket->GetRemoteAddress() << endl;
			break;
		case sf::Socket::Disconnected:
			cout << c->socket->GetRemoteAddress() << " has disconnected" << endl;
			towipe.push(c);
			break;
		case sf::Socket::NotReady:
			cout << c->socket->GetRemoteAddress() << " is not ready" << endl;
			break;
		}
	}
	while (!towipe.empty()) {
		delete towipe.top();
		towipe.pop();
	}
	//Other server stuff
	//Everything happens here
	sf::Sleep(0.01);
	return true;
}

void NLS::Unload() {

}