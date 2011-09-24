////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

map <int, NLS::WorldServer*> NLS::WorldServer::instances;

void NLS::WorldServer::Start(int n) {
	if (n == -1) {
		Start(0);
		Start(1);
	} else {
		cout << "INFO: Starting up WorldServer #" << n << endl;
		if (instances.find(n) != instances.end()) {
			cout << "WARNING: WorldServer #" << n << " already exists!" << endl;
			Shutdown(n);
		}
		instances[n] = new WorldServer(n);
	}
}

NLS::WorldServer::WorldServer(int n) {
	done = false;
	thread = new sf::Thread([&](){this->Loop();});
	thread->Launch();
	cout << "INFO: WorldServer #" << n << " up and running" << endl;
}

void NLS::WorldServer::Loop() {
	while (!done) {
		sf::Sleep(0.1);
	}
}

void NLS::WorldServer::Shutdown(int n) {
	if (n == -1) {
		for (auto it = instances.begin(); it != instances.end(); it++) {
			cout << "INFO: Shutting down WorldServer #" << it->first << endl;
			it->second->done = true;
			it->second->thread->Wait();
			delete it->second;
		}
		instances.clear();
	} else {
		auto it = instances.find(n);
		if (it == instances.end()) {
			cout << "WARNING: Unable to find WorldServer #" << n << endl;
		} else {
			cout << "INFO: Shutting down WorldServer #" << n << endl;
			it->second->done = true;
			it->second->thread->Wait();
			delete it->second;
			instances.erase(it);
		}
	}
}