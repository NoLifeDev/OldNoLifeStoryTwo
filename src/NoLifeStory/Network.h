////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Network {
		void Init();
		void Loop();
		void Unload();
		extern bool Online;
		extern uint16_t Version;
		extern string Patch;
		extern uint32_t SendIV;
		extern uint32_t RecvIV;
		extern uint8_t Locale;
	}
	class Packet {
	private:
		Packet(const Packet& p) {}
	public:
		uint16_t opcode;
		vector<char> data;
		size_t pos;
		Packet() : pos(0), data(), opcode(0) {}
		void Send();
		template <class T>
		T Read() {
			T& ret = *(T*)&data[pos];
			pos += sizeof(T);
			return ret;
		}
		template <class T>
		T Write(T v) {
			data.insert(data.end(), (char*)&v, (char*)&v+sizeof(T));
		}
	};
	template <>
	inline string Packet::Read<string>() {
		size_t size = Read<uint16_t>();
		string s(&data[pos], size);
		pos += size;
		return s;
	}
	template <>
	inline string Packet::Write<string>(string s) {
		Write<uint16_t>(s.size());
		data.insert(data.end(), s.begin(), s.end());
	}
}
