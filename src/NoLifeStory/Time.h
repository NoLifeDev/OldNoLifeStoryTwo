////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class _Time {
		sf::Clock clock;
	public:
		void Reset();
		void Step();
		uint32_t delta;
		uint32_t tdelta;
		double fps;
		bool output;
	} extern Time;
};