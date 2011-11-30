////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
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

		string ReadStringLen(int32_t length);
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
	inline bool Packet::Read<bool>() {
		return Read<uint8_t>() != 0;
	}
	inline string Packet::ReadStringLen(int32_t length) {
		stringstream ret;
		for (auto i = 0; i < length; i++) {
			if (data[pos + i] == 0x00) break;
			ret << (char)data[pos + i];
		}
		pos += length;
		return ret.str();
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
	template <>
	inline void Packet::Write<bool>(bool v) {
		Write<int8_t>(v ? 1 : 0);
	}

	namespace PacketHandlers {
		void RegisterHandlers();
		void HandlePing(Packet &);
		void HandleChangeMap(Packet &);
		void HandlePlayerSpawn(Packet &);
		void HandlePlayerDespawn(Packet &);
	}
}
