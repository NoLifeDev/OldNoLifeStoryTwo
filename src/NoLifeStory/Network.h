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
		extern uint8_t SendIV[4];
		extern uint8_t RecvIV[4];
		extern uint8_t Locale;
		extern string IP;
		extern uint16_t Port;
	}
	class Packet {
	public:
		vector<uint8_t> data;
		size_t pos;
		static map<uint16_t, function<void(Packet&)>> Handlers;
		Packet() : pos(0), data() {}
		Packet(uint16_t opcode) : pos(0), data() {
			Write<int32_t>(0);
			Write<uint16_t>(opcode);
		}
		Packet(uint8_t* data, uint16_t len) : pos(0), data(data, data+len) {}
		void Send();
		void Encrypt();
		void Decrypt();
		string ToString();
		template <class T>
		T Read() {
			T& ret = *(T*)&data[pos];
			pos += sizeof(T);
			return ret;
		}
		template <class T>
		void Write(T v) {
			data.insert(data.end(), (uint8_t*)&v, (uint8_t*)&v+sizeof(T));
		}
	};
	template <>
	inline string Packet::Read<string>() {
		size_t size = Read<uint16_t>();
		string s((char*)&data[pos], size);
		pos += size;
		return s;
	}
	template <>
	inline void Packet::Write<string>(string s) {
		Write<uint16_t>(s.size());
		data.insert(data.end(), s.begin(), s.end());
	}
	inline string Packet::ToString() {
		std::stringstream out;
		for (int i = 0; i < data.size(); ++i) {
			out << hex << uppercase << setw(2) << setfill('0') << (uint16_t)data[i];
			out << ' ';
		}
		return out.str();
	}
}
