////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Network {
		void Init();
		void Loop();
		void Check();
		void Unload();
		extern bool Online;
		extern uint16_t Version;
		extern string Patch;
		extern uint32_t SendIV;
		extern uint32_t RecvIV;
		extern uint8_t Locale;
	}
	class Packet {
	public:
		uint16_t opcode;
		vector<char> data;
		size_t pos;
		Packet() : pos(0), data(), opcode(0) {pos = 0;}
		Packet(const Packet& p) : pos(0), opcode(p.opcode), data(p.data) {}
		Packet(Packet&& p) : pos(0), opcode(p.opcode), data(p.data) {}
		void Push();//Pushes the packet to the list of stuff to send
		void Send();//Encrypts and sends it off
		void Handle();//Call the appropriate function
		void Receive();//Get and decrypt a packet of data
		template <class T>
		T Read() {
			T& ret = *(T*)&data[pos];
			pos += sizeof(T);
			return ret;
		}
		template <>
		string Read<string>() {
			size_t size = Read<uint16_t>();
			string s(&data[pos], size);
			pos += size;
			return s;
		}
	};
}