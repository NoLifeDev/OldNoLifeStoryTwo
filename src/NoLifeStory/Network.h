////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Packet;
	namespace Network {
		void Init();
		void Loop();
		void Unload();
		extern sf::TcpSocket Socket;
		extern bool Online;
		extern bool Connected;
		extern uint16_t Version;
		extern string Patch;
		extern uint8_t SendIV[4];
		extern uint8_t RecvIV[4];
		extern uint8_t Locale;
		extern string IP;
		extern uint16_t Port;
	}

	namespace Locales {
		// Credits: Vana (Bui)
		const int8_t Korea = 0x01;
		const int8_t Japan = 0x03;
		const int8_t China = 0x05;
		const int8_t Sea = 0x07;
		const int8_t Thailand = 0x07;
		const int8_t Global = 0x08;
		const int8_t Europe = 0x09;
		const int8_t Brazil = 0x09;
		const int8_t Taiwan = 0x3C; // Not sure about this one!
		const int8_t Vietnam = 0x00;

		const int8_t KoreaTest = 0x02;
		const int8_t ChinaTest = 0x04;
		const int8_t GlobalTest = 0x05;
		const int8_t TaiwanTest = 0x06;
		const int8_t EuropeTest = 0x00;
		const int8_t JapanTest = 0x00;
	}
}