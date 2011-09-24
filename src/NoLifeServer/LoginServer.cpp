////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::LoginServer *NLS::LoginServer::instance = nullptr;

void NLS::LoginServer::Start() {
	if (instance != nullptr) {
		cout << "WARNING: Instance of LoginServer already exists!" << endl;
		Shutdown();
	}
	cout << "INFO: Starting up LoginServer" << endl;
	instance = new LoginServer();
}

NLS::LoginServer::LoginServer() {
	done = false;
	listener.SetBlocking(false);
	if (listener.Listen(8484) == sf::Socket::Error) {
		cerr << "ERROR: LoginServer failed to listen on port 8484" << endl;
		throw(273);
	}
	thread = new sf::Thread([&](){this->Loop();});
	thread->Launch();
	cout << "INFO: LoginServer up and listening on port 8484" << endl;
}

void NLS::LoginServer::Loop() {
	while (!done) {
		static sf::TcpSocket* next(new sf::TcpSocket());
		if (listener.Accept(*next) == sf::Socket::Done) {
			cout << "INFO: Player connected from " << next->GetRemoteAddress() << ":" << next->GetRemotePort() << endl;
			//Do stuff with next
			next = new sf::TcpSocket();
		}
		sf::Sleep(0.1);
	}
}

void NLS::LoginServer::Shutdown() {
	cout << "INFO: Shutting down LoginServer" << endl;
	instance->done = true;
	instance->thread->Wait();
	delete instance;
	instance = nullptr;
}