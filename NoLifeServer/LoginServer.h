///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace NLS {
	class LoginServer {
	public:
		LoginServer();
		void Loop();
	private:
		sf::Thread* thread;
	};
};