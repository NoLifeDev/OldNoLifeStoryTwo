////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::LoginServer::LoginServer() {
	thread = new sf::Thread([&](){this->Loop();});
	thread->Launch();
}

void NLS::LoginServer::Loop() {
	while (true) {
		//Do cool stuff
		sf::Sleep(0.1);
	}
}