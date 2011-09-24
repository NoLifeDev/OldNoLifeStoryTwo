///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace NLS {
	class WorldServer {
	public:
		static void Start(int n = -1);
		static void Shutdown(int n = -1);
	private:
		WorldServer(int n);
		void Loop();
		bool done;
		sf::Thread* thread;
		static map <int, WorldServer*> instances;
	};
};