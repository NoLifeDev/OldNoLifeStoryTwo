////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class _Time {
#ifdef NLS_CPP11
		chrono::high_resolution_clock clock;
		chrono::high_resolution_clock::time_point last;
		chrono::high_resolution_clock::time_point start;
#else
		sf::Clock clock;
#endif
	public:
		void Reset();
		void Step();
		double delta;
		double tdelta;
		double fps;
		bool output;
	} extern Time;
}
