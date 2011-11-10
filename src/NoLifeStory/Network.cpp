////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

sf::TcpSocket NLS::Network::Socket;

bool NLS::Network::Online;
uint16_t NLS::Network::Version;
string NLS::Network::Patch;
uint32_t NLS::Network::SendIV;
uint32_t NLS::Network::RecvIV;
uint8_t NLS::Network::Type;
#ifdef NLS_CPP11
thread* NLS::Network::Thread;
#else
sf::Thread* NLS::Network::Thread;
#endif

inline void Receive(char* data, size_t size) {
	while (size > 0) {
		size_t received;
		NLS::Network::Socket.Receive(data, size, received);
		size -= received;
		data += received;
	}
}
template <class T>
inline T& Get (char*& data) {
	T& ret = *(T*)data;
	data += sizeof(T);
	return ret;
}
void NLS::Network::Init() {
	Socket.SetBlocking(true);
	if (Socket.Connect("63.251.217.2", 8484, 2000) != sf::Socket::Done) {
		cerr << "Failed to connect to server at " << string(Socket.GetRemoteAddress().ToString()) << endl;
		Online = false;
		return;
	} else {
		cout << "Connected to LoginServer at " << string(Socket.GetRemoteAddress().ToString())  << endl;
		Online = true;
	}
	char* lengthd = new char[2];
	Receive(lengthd, 2);
	size_t length = Get<uint16_t>(lengthd);
	char* header = new char[length];
	Receive(header, length);
	Version = Get<uint16_t>(header);
	Patch = string(header);
	header += Patch.length()+1;
	SendIV = Get<uint32_t>(header);
	RecvIV = Get<uint32_t>(header);
	Type = Get<uint8_t>(header);
	cout << "LoginServer version: " << Version << endl;
	cout << "Patch location: " << Patch << endl;
	cout << "Type: " << (uint16_t)Type << endl;
	cout << "SendIV: " << SendIV << endl;
	cout << "RecvIV: " << RecvIV << endl;
	Socket.SetBlocking(false);
#ifdef NLS_CPP11
		Thread = new thread(Loop);
#else
		Thread = new sf::Thread(Loop);
#endif
}

void NLS::Network::Loop() {
	while (true) {
		sf::Sleep(100);
	}
}