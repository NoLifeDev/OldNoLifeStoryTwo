///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace NLS {
	class LoginServer {
	public:
		static void Start();
		static void Shutdown();
	private:
		LoginServer();
		void Loop();
		bool done;
		sf::Thread *thread;
		sf::TcpListener listener;
		static LoginServer *instance;
	};
};