///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

set<NLS::Connection*> NLS::Connections;

NLS::Connection::Connection(sf::TcpSocket* socket) {
	this->socket = socket;
	Connections.insert(this);
}

NLS::Connection::~Connection() {
	delete socket;
	Connections.erase(this);
}