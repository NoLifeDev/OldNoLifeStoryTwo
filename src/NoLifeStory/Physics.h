////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Physics {
	public:
		double x, y, r;
		double vx, vy, vr;
		Foothold* fh;
		LadderRope* lr;
		int layer, group;
		int freefall;
		bool left, right, up, down;
		bool f;
		bool notAPlayer;
		float speedMin;
		Foothold* djump;
		Physics();
		Physics(double x, double y);
		void Update();
		void Reset(double x, double y);
		void Jump();
		void MouseFly();
		static void Init();
	};
}
