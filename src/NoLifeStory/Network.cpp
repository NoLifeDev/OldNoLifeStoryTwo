////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Network::Online;
uint16_t NLS::Network::Version;
string NLS::Network::Patch;
uint8_t NLS::Network::SendIV[4];
uint8_t NLS::Network::RecvIV[4];
uint8_t NLS::Network::Locale;
string NLS::Network::IP;
uint16_t NLS::Network::Port;
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

void SendHandshakeOK();
void EncryptPacket(unsigned char* data, int32_t length);
void DecryptPacket(unsigned char* data, int32_t length);
void NextIV(uint8_t *oldiv);
void CreateHeader(uint8_t* header, uint16_t version, uint16_t length, uint8_t* IV);

void NLS::Network::Init() {
	Socket.SetBlocking(true);
	if (Socket.Connect(IP, Port, 2000) != sf::Socket::Done) {
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
	uint32_t siv = Get<uint32_t>(header);
	uint32_t riv = Get<uint32_t>(header);
	Locale = Get<uint8_t>(header);
	cout << "Server version: " << Version << endl;
	cout << "Patch location: " << Patch << endl;
	cout << "Locale: " << (uint16_t)Locale << endl;
	cout << "SendIV: " << siv << endl;
	cout << "RecvIV: " << riv << endl;
	memcpy(SendIV, &siv, 4);
	memcpy(RecvIV, &riv, 4);
	Socket.SetBlocking(false);

	SendHandshakeOK();

	NLS::Packet packet(0x18);
	packet.Send();
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
		case sf::Socket::Disconnected:
			cerr << "Disconnected from the server" << endl;
			Online = false;
			Socket.Disconnect();
			return false;
		case sf::Socket::Error:
			cerr << "Network error occured" << endl;
			Online = false;
			Socket.Disconnect();
			return false;
		case sf::Socket::NotReady:
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
			DecryptPacket((uint8_t *)data, len);
			cout << "Packet: ";
			std::stringstream out;
			for (int i = 0; i < len; ++i) {
				out << hex << uppercase << setw(2) << setfill('0') << (uint16_t)data[i];
				out << ' ';
			}
			cout << out.str() << endl;
			ghead = true;
			pos = 0;
		}
	}
}

void NLS::Network::Unload() {

}

void NLS::Packet::Send() {
	CreateHeader((uint8_t *)data.data(), NLS::Network::Version, (uint16_t)data.size() - 4, NLS::Network::SendIV);
	unsigned char * d = ((uint8_t *)data.data()) + 4;
	EncryptPacket(d, data.size() - 4);
	Socket.Send(data.data(), data.size());
}

void SendHandshakeOK() {
	// Depends on the versions.
	using namespace NLS::Network;
	if (Locale == 0x08 && Version <= 100) return; // GMS V.100 and lower didn't have this.
	if (Locale == 0x07 && Version <= 111) return; // MSEA V.101 and lower didn't have this. |NOTSURE|

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

uint8_t rol(uint8_t value, int32_t times) {
	int32_t highbit;
	for (auto i = 0; i < times; i++) {
		highbit = ((value & 0x80) ? 1 : 0);
		value <<= 1;
		value |= highbit;
	}
	return value;
}

uint8_t ror(uint8_t value, int32_t times) {
	int32_t lowbit;
	for (auto i = 0; i < times; i++) {
		lowbit = ((value & 1) ? 1 : 0);
		value >>= 1;
		value |= (lowbit << 7);
	}
	return value;
}

void EncryptPacket(unsigned char *buf, int32_t size) {
	int32_t j;
	uint8_t a, c;
	for (uint8_t i = 0; i < 3; i++) {
		a = 0;
		for (j = size; j > 0; j--) {
			c = buf[size - j];
			c = rol(c, 3);
			c = (uint8_t)(c + j); // Guess this is supposed to be right?
			c = c ^ a;
			a = c;
			c = ror(a, j);
			c = c ^ 0xFF;
			c = c + 0x48;
			buf[size - j] = c;
		}
		a = 0;
		for (j = size; j > 0; j--) {
			c = buf[j - 1];
			c = rol(c, 4);
			c = (uint8_t)(c + j); // Guess this is supposed to be right?
			c = c ^ a;
			a = c;
			c = c ^ 0x13;
			c = ror(c, 3);
			buf[j - 1] = c;
		}
	}

	Crypto::TransformData(NLS::Network::SendIV, buf, size);
	NextIV(NLS::Network::SendIV);
}

void DecryptPacket(unsigned char *buf, int32_t size) {
	Crypto::TransformData(NLS::Network::RecvIV, buf, size);
	NextIV(NLS::Network::RecvIV);

	int32_t j;
	uint8_t a, b, c;
	for (uint8_t i = 0; i < 3; i++) {
		a = 0;
		b = 0;
		for (j = size; j > 0; j--) {
			c = buf[j - 1];
			c = rol(c, 3);
			c = c ^ 0x13;
			a = c;
			c = c ^ b;
			c = (uint8_t)(c - j); // Guess this is supposed to be right?
			c = ror(c, 4);
			b = a;
			buf[j - 1] = c;
		}
		a = 0;
		b = 0;
		for (j = size; j > 0; j--) {
			c = buf[size - j];
			c = c - 0x48;
			c = c ^ 0xFF;
			c = rol(c, j);
			a = c;
			c = c ^ b;
			c = (uint8_t)(c - j); // Guess this is supposed to be right?
			c = ror(c, 3);
			b = a;
			buf[size - j] = c;
		}
	}

}

void NextIV(uint8_t *oldiv) {
	uint8_t newIV[4] = { 0xF2, 0x53, 0x50, 0xC6 };

	for (auto i = 0; i < 4; i++) {
		uint8_t input = oldiv[i], tableInput = ShuffleKey[input];
		newIV[0] += ShuffleKey[newIV[1]] - input;
		newIV[1] -= newIV[2] ^ tableInput;
		newIV[2] ^= ShuffleKey[newIV[3]] + input;
		newIV[3] -= newIV[0] - tableInput;

		uint32_t merged = (uint32_t)((newIV[3] << 24) | (newIV[2] << 16) | (newIV[1] << 8) | newIV[0]);
		uint32_t shifted = (uint32_t)((merged << 3) | (merged >> 0x1D));

		newIV[0] = shifted;
		newIV[1] = shifted >> 8;
		newIV[2] = shifted >> 16;
		newIV[3] = shifted >> 24;
	}

	for (auto i = 0; i < 4; i++) {
		oldiv[i] = newIV[i]; // Transferring all bytes!
	}
}

void CreateHeader(uint8_t* header, uint16_t version, uint16_t length, uint8_t* IV) {
	uint16_t a = (IV[3] << 8) + IV[2];
	a ^= version;
	uint16_t b = a ^ length;
	header[0] = a % 0x100;
	header[1] = a / 0x100;
	header[2] = b % 0x100;
	header[3] = b / 0x100;
}

#pragma endregion