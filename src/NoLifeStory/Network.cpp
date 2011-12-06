////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Network::Online = true;
bool NLS::Network::Connected = false;
uint16_t NLS::Network::Version;
string NLS::Network::Patch;
uint8_t NLS::Network::SendIV[4];
uint8_t NLS::Network::RecvIV[4];
uint8_t NLS::Network::Locale;
string NLS::Network::IP;
uint16_t NLS::Network::Port;
vector<NLS::Packet> ToSend;
sf::TcpSocket NLS::Network::Socket;

void SendHandshakeOK();

void NLS::Network::Init() {
	Socket.SetBlocking(false);
	Connected = false;
}

void NLS::Network::Loop() {
	static Packet p;
	static bool ghead = true;
	static bool initial = true;
	static bool connecting = false;
	static size_t pos = 0;
	static uint16_t len = 0;
	static uint8_t header[4];
	static uint8_t data[0x10000];
	static double timeout = 0;
	auto Receive = [&](uint8_t* data, size_t len) -> bool{
		size_t received = 0;
		sf::Socket::Status err = Socket.Receive((char *)data+pos, len-pos, received);
		pos += received;
		switch (err) {
		case sf::Socket::Disconnected:
			if (!connecting) {
				cerr << "Disconnected from the server" << endl;
				Connected = false;
				Online = false;
				//TODO - Pop up message saying they got disconnected and ask if they want to play offline, or login again.
				Map::Load("0", "");
			} else {
				cerr << "Failed to connect to the server" << endl;
#ifdef _WIN32
				cerr << "WSAGetLastError(): " << WSAGetLastError() << endl;
#endif
				Connected = false;
				Online = false;
				//TODO - Pop up message saying unable to connect and ask if they want to play offline, or retry to connect.
				Map::Load("0", "");
			}
			return false;
		case sf::Socket::Error:
			cerr << "Network error occured " << endl;
			Connected = false;
			Online = false;
			return false;
		case sf::Socket::NotReady:
			if (connecting and timeout > 5000) {
				cerr << "Connection to the server timed out" << endl;
				Connected = false;
				Online = false;
				//TODO - Pop up message saying unable to connect and ask if they want to play offline, or retry to connect.
				Map::Load("0", "");
			}
			return false;
		default:
			connecting = false;
		}
		return pos == len;
	};
	if (!Online) return;
	if (!Connected) {
		Socket.Connect(IP, Port);
		Connected = true;
		connecting = true;
		initial = true;
		ghead = true;
		pos = 0;
		timeout = 0;
	}
	timeout += Time::delta;
	while (true) {
		if (initial) {
			if (ghead) {
				if (!Receive(header, 2)) return;
				len = *(uint16_t*)header;
				ghead = false;
				pos = 0;
			} else {
				if (!Receive(data, len)) return;
				Packet p(data, len);
				Version = p.Read<uint16_t>();
				Patch = p.Read<string>();
				uint32_t siv = p.Read<uint32_t>();
				uint32_t riv = p.Read<uint32_t>();
				Locale = p.Read<uint8_t>();
				cout << "Connected to server at " << IP << ":" << Port << endl;
				cout << "Server version: " << Version << endl;
				cout << "Minor version: " << Patch << endl;
				cout << "Locale: " << (uint16_t)Locale << endl;
				cout << "SendIV: " << siv << endl;
				cout << "RecvIV: " << riv << endl;
				memcpy(SendIV, &siv, 4);
				memcpy(RecvIV, &riv, 4);
				Handle::Init();
				Send::Handshake();
				Send::Pang();
				initial = false;
				ghead = true;
				pos = 0;
			}
		} else {
			if (ghead) {
				if (!Receive(header, 4)) return;
				uint32_t llen = *(uint32_t*)header;
				len = (llen>>16)^llen;
				ghead = false;
				pos = 0;
			} else {
				if (!Receive(data, len)) return;
				Packet p(data, len);
				p.Decrypt();
				cout << "Received Packet: " << p.ToString() << endl;
				uint16_t opcode = p.Read<uint16_t>();
				auto& f = p.Handlers[opcode];
				if (f) f(p);
				else cerr << "No packet handler for opcode: " << opcode << endl;
				ghead = true;
				pos = 0;
				break;
			}
		}
	}
}

void NLS::Network::Unload() {

}