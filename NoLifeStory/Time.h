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
		double delta;
		double tdelta;
	} extern Time;
};