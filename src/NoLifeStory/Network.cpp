////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Network::Online;
uint16_t NLS::Network::Version;
string NLS::Network::Patch;
uint32_t NLS::Network::SendIV;
uint32_t NLS::Network::RecvIV;
uint8_t NLS::Network::Locale;
vector<NLS::Packet> ToSend;
vector<NLS::Packet> ToRecv;
sf::TcpSocket Socket;
#ifdef NLS_CPP11
thread* Thread;
mutex SendMutex;
mutex RecvMutex;
atomic<bool> Done;
#else
sf::Thread* Thread;
sf::Mutex SendMutex;
sf::Mutex RecvMutex;
bool Done;
#endif

inline void Receive(char* data, size_t size) {
	while (size > 0) {
		if (Done) {
			return;
		}
		if (SendMutex.try_lock()) {
			while (!ToSend.empty()) {
				ToSend.back().Send();
				ToSend.pop_back();
			}
			SendMutex.unlock();
		}
		size_t received;
		Socket.Receive(data, size, received);
		size -= received;
		data += received;
	}
}
template <class T>
inline T Get (char*& data) {
	T& ret = *(T*)data;
	data += sizeof(T);
	return ret;
}
template <>
inline string Get<string> (char*& data) {
	size_t size = Get<uint16_t>(data);
	string s(data, size);
	data += size;
	return s;
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
	Patch = Get<string>(header);
	SendIV = Get<uint32_t>(header);
	RecvIV = Get<uint32_t>(header);
	Locale = Get<uint8_t>(header);
	cout << "LoginServer version: " << Version << endl;
	cout << "Patch location: " << Patch << endl;
	cout << "Locale: " << (uint16_t)Locale << endl;
	cout << "SendIV: " << SendIV << endl;
	cout << "RecvIV: " << RecvIV << endl;
	Socket.SetBlocking(false);
	Done = false;
#ifdef NLS_CPP11
	Thread = new thread(Loop);
#else
	Thread = new sf::Thread(Loop);
#endif
}
void NLS::Network::Loop() {
	while (!Done) {
		Packet p;
		p.Receive();
	}
}
void NLS::Network::Check() {
	RecvMutex.lock();
	while (!ToRecv.empty()) {
		ToRecv.back().Handle();
		ToRecv.pop_back();
	}
	RecvMutex.unlock();
}
void NLS::Network::Unload() {
	Done = true;
	Thread->join();
}

void NLS::Packet::Send() {
	Socket.Send(data.data(), data.size());
}
void NLS::Packet::Receive() {
	char header[4];
	::Receive(header, 4);
	uint32_t& length = *(uint32_t*)header;
	length = (length>>16)^(length&0xFFFF);
	char* raw = new char[length];
	::Receive(raw, length);
	cout << "Packet: ";
	for (int i = 0; i < length; ++i) {
		cout << ios::hex << setw(2) << (int)(uint8_t)raw[i] << " ";
	}
	cout << ios::dec;
	//Decrypt the packet
	delete[] raw;
	RecvMutex.lock();
	ToRecv.push_back(*this);
	RecvMutex.unlock();
}
void NLS::Packet::Push() {
	//Encrypt the packet
	SendMutex.lock();
	ToSend.push_back(*this);
	SendMutex.unlock();
}
void NLS::Packet::Handle() {

}