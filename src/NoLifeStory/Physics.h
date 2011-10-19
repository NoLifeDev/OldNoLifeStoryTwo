////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Physics {//Derive anything with physics from this
	public:
		double x, y;
		double vx, vy;
		Foothold* fh;
		class LadderRope* lr;
		int layer, group;
		int freefall;
		Physics();
		Physics(double x, double y);
		void Update();
		void Reset(double x, double y);
		static void Init();
	};
}
