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
sf::TcpSocket Socket;

inline void Receive(char* data, size_t size) {
	while (size > 0) {
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
	cout << "Server version: " << Version << endl;
	cout << "Patch location: " << Patch << endl;
	cout << "Locale: " << (uint16_t)Locale << endl;
	cout << "SendIV: " << SendIV << endl;
	cout << "RecvIV: " << RecvIV << endl;
	Socket.SetBlocking(false);
}
void NLS::Network::Loop() {
	static Packet p;
	static bool ghead = true;
	static size_t pos = 0;
	static uint32_t len = 0;
	static char header[4];
	static char data[0x10000];
	auto Receive = [&](char* data, size_t len) -> bool{
		size_t received = 0;
		sf::Socket::Status err = Socket.Receive(data+pos, len-pos, received);
		pos += received;
		switch (err) {
		case sf::Socket::Status::Disconnected:
			cerr << "Disconnected from the server" << endl;
			Online = false;
			Socket.Disconnect();
			return false;
		case sf::Socket::Status::Error:
			cerr << "Network error occured" << endl;
			Online = false;
			Socket.Disconnect();
			return false;
		case sf::Socket::Status::NotReady:
			return false;
		}
		if (received == 0) {
			return false;
		}
		return pos == len;
	};
	while (true) {
		if (ghead) {
			if (!Receive(header, 4)) {
				return;
			}
			len = *(uint32_t*)header;
			len = (len>>16)^(len&0xFFFF);
			ghead = false;
			pos = 0;

		} else {
			if (!Receive(data, len)) {
				return;
			}
			cout << "Packet: ";
			std::stringstream out;
			for (int i = 0; i < len; ++i) {
				out << ios::hex << ios::uppercase << setw(2) << setfill('0') << (uint16_t)*(uint8_t*)&data[i];
				out << ' ';
			}
			cout << out << endl;
			ghead = true;
			pos = 0;
		}
	}
}
void NLS::Network::Unload() {

}
void NLS::Packet::Send() {
	//Encrypt the packet
	Socket.Send(data.data(), data.size());
}