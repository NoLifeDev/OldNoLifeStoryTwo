////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Network::Online = true;
uint16_t NLS::Network::Version;
string NLS::Network::Patch;
uint8_t NLS::Network::SendIV[4];
uint8_t NLS::Network::RecvIV[4];
uint8_t NLS::Network::Locale;
string NLS::Network::IP;
uint16_t NLS::Network::Port;
vector<NLS::Packet> ToSend;
sf::TcpSocket Socket;
map<uint16_t, function<void(NLS::Packet&)>> NLS::Packet::Handlers;

void SendHandshakeOK();
void NextIV(uint8_t *oldiv);

void NLS::Network::Init() {
	Socket.SetBlocking(false);
}

void NLS::Network::Loop() {
	static Packet p;
	static bool ghead = true;
	static bool initial = true;
	static bool connected = false;
	static bool connecting = false;
	static size_t pos = 0;
	static uint16_t len = 0;
	static uint8_t header[4];
	static uint8_t data[0x10000];
	auto Receive = [&](uint8_t* data, size_t len) -> bool{
		size_t received = 0;
		sf::Socket::Status err = Socket.Receive((char *)data+pos, len-pos, received);
		pos += received;
		switch (err) {
		case sf::Socket::Disconnected:
			if (!connecting) {
				cerr << "Disconnected from the server" << endl;
				connected = false;
				Online = false;
			}
			return false;
		case sf::Socket::Error:
			cerr << "Network error occured " << endl;
#if _WIN32
			cerr << "[DEBUGINFO] WSAGetLastError: " << WSAGetLastError() << endl;
#endif
			connected = false;
			Online = false;
			return false;
		case sf::Socket::NotReady:
			return false;
		default:
			connecting = false;
		}
		return pos == len;
	};
	if (!Online) return;
	if (!connected) {
		Socket.Connect(IP, Port);
		connected = true;
		connecting = true;
		initial = true;
		ghead = true;
		pos = 0;
	}
	while (true) {
		if (initial) {
			if (ghead) {
				if (!Receive(header, 2)) {
					return;
				}
				len = *(uint16_t*)header;
				ghead = false;
				pos = 0;
			} else {
				if (!Receive(data, len)) {
					return;
				}
				Packet p(data, len);
				Version = p.Read<uint16_t>();
				Patch = p.Read<string>();
				uint32_t siv = p.Read<uint32_t>();
				uint32_t riv = p.Read<uint32_t>();
				Locale = p.Read<uint8_t>();
				cout << "Server version: " << Version << endl;
				cout << "Patch location: " << Patch << endl;
				cout << "Locale: " << (uint16_t)Locale << endl;
				cout << "SendIV: " << siv << endl;
				cout << "RecvIV: " << riv << endl;
				memcpy(SendIV, &siv, 4);
				memcpy(RecvIV, &riv, 4);
				SendHandshakeOK();
				NLS::Packet packet(0x18);
				packet.Send();
				cout << "Connected to server at " << IP << ":" << Port << endl;
				initial = false;
				ghead = true;
				pos = 0;
			}
		} else {
			if (ghead) {
				if (!Receive(header, 4)) {
					return;
				}
				uint32_t llen = *(uint32_t*)header;
				len = (llen>>16)^llen;
				ghead = false;
				pos = 0;
			} else {
				if (!Receive(data, len)) {
					return;
				}
				Packet p(data, len);
				p.Decrypt();
				cout << "Packet: " << p.ToString() << endl;
				uint16_t opcode = p.Read<uint16_t>();
				auto& f = p.Handlers[opcode];
				if (f) {
					f(p);
				} else {
					cerr << "No packet handler for opcode: " << opcode << endl;
				}
				ghead = true;
				pos = 0;
			}
		}
	}
}

void NLS::Network::Unload() {

}

void NLS::Packet::Send() {
	uint16_t a = (Network::SendIV[3]<<8)+Network::SendIV[2];
	a ^= Network::Version;
	uint16_t b = a^(data.size()-4);
	data[0] = a%0x100;
	data[1] = a/0x100;
	data[2] = b%0x100;
	data[3] = b/0x100;
	Encrypt();
	Socket.Send((char*)data.data(), data.size());
}

void SendHandshakeOK() {
	// Depends on the versions.
	using namespace NLS::Network;
	if (Locale == 0x08 && Version <= 100) return; // GMS V.100 and lower didn't have this.
	if (Locale == 0x07 && Version <= 111) return; // MSEA V.111 and lower didn't have this. |NOTSURE|

	uint16_t subversion = atoi(Patch.c_str());
	uint16_t header = 0;
	if (Locale == 0x08) {
		if (Version >= 101) header = 0x14;
	}
	else if (Locale == 0x09) {
		if (Version >= 112) header = 0x01; // No shit!
	}

	NLS::Packet packet(header);
	packet.Write<uint8_t>(Locale);
	packet.Write<uint16_t>(Version);
	packet.Write<uint16_t>(subversion);
	packet.Send();
}

#pragma region Encryption Stuff
#ifndef _WIN32
unsigned int _rotl8(uint8_t value, int shift)
{
	return (value<<shift)|(value>>(8-shift));
}

unsigned int _rotr8(uint8_t value, int shift)
{
	return (value>>shift)|(value<<(8-shift));
}
#endif //_WIN32

void NLS::Packet::Encrypt() {
	int32_t j;
	uint8_t a, c;
	uint8_t* buf = data.data()+4;
	size_t size = data.size()-4;
	
	for (uint8_t i = 0; i < 3; i++) {
		a = 0;
		for (j = size; j > 0; j--) {
			c = buf[size-j];
			c = _rotl8(c, 3);
			c += j;
			c ^= a;
			a = c;
			c = _rotr8(c, j);
			c = ~c;
			c += 0x48;
			buf[size-j] = c;
		}
		a = 0;
		for (j = size; j > 0; j--) {
			c = buf[j-1];
			c = _rotl8(c, 4);
			c += j;
			c ^= a;
			a = c;
			c ^= 0x13;
			c = _rotr8(c, 3);
			buf[j-1] = c;
		}
	}
	
	Crypto::TransformData(NLS::Network::SendIV, buf, size);
	NextIV(NLS::Network::SendIV);
}

void NLS::Packet::Decrypt() {
	uint8_t* buf = data.data(); // NO HEADERS HERE!!!
	size_t size = data.size();
	Crypto::TransformData(NLS::Network::RecvIV, buf, size);
	NextIV(NLS::Network::RecvIV);
	int32_t j;
	uint8_t a, b, c;
	for (uint8_t i = 0; i < 3; i++) {
		a = 0;
		b = 0;
		for (j = size; j > 0; j--) {
			c = buf[j-1];
			c = _rotl8(c, 3);
			c ^= 0x13;
			a = c;
			c ^= b;
			c -= j;
			c = _rotr8(c, 4);
			b = a;
			buf[j-1] = c;
		}
		a = 0;
		b = 0;
		for (j = size; j > 0; j--) {
			c = buf[size-j];
			c -= 0x48;
			c = ~c;
			c = _rotl8(c, j);
			a = c;
			c ^= b;
			c -= j;
			c = _rotr8(c, 3);
			b = a;
			buf[size-j] = c;
		}
	}
}

void NextIV(uint8_t *oldiv) {
	uint8_t newIV[4] = { 0xF2, 0x53, 0x50, 0xC6 };

	for (auto i = 0; i < 4; i++) {
		uint8_t input = oldiv[i];
		uint8_t tableInput = ShuffleKey[input];
		newIV[0] += ShuffleKey[newIV[1]]-input;
		newIV[1] -= newIV[2]^tableInput;
		newIV[2] ^= ShuffleKey[newIV[3]]+input;
		newIV[3] -= newIV[0]-tableInput;

		uint32_t& merged = *(uint32_t*)newIV;
		merged = merged<<3|merged>>0x1D;
	}

	for (auto i = 0; i < 4; i++) {
		oldiv[i] = newIV[i]; // Transferring all bytes!
	}
}

#pragma endregion