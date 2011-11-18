////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	extern sf::Window* window;
	extern bool Fullscreen;
	namespace Graphics {
		void Init();
		void Draw();
		void Unload();
		extern bool NPOT;
		extern bool Shit;
	}
}
