////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Network {
		extern sf::TcpSocket Socket;
		void Init();
		void Loop();
		extern bool Online;
		extern uint16_t Version;
		extern string Patch;
		extern uint32_t SendIV;
		extern uint32_t RecvIV;
		extern uint8_t Type;
#ifdef NLS_CPP11
		extern thread* Thread;
#else
		extern sf::Thread* Thread;
#endif
	}
	class Packet {
	public:
	};
}
