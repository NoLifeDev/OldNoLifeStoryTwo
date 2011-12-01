////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	struct Movement;
	class Physics {
	public:
		double x, y, r;
		double vx, vy, vr;
		double lastx, lasty;
		Foothold* fh;
		LadderRope* lr;
		int layer, group;
		int freefall;
		int lastAction;
		bool left, right, up, down;
		bool didLieDown;
		bool f;
		bool notAPlayer, control;
		float speedMin;
		Foothold* djump;
		vector<Movement> moves;
		Physics();
		Physics(double x, double y);
		void Update();
		void Reset(double x, double y);
		void Jump();
		void MouseFly();
		void AddMovement(int8_t action);
		static void Init();
		static string StanceToString(int8_t stance);
	};

	struct Movement {
		/// Types
		// 10 = stand up from chair lol
		// 11 = downjump
		// 4 = teleport
		// 1 = jump
		// 3/0 = walk
		Movement(int8_t type, int8_t stance, int16_t x, int16_t y, int16_t fh, int16_t time = 30) : type(type), stance(stance), x(x), y(y), fh(fh), t(time), vx(0), vy(0) {}
		Movement(int8_t type) : type(type) {}
		int8_t type, stance;
		int16_t x, y, vx, vy, fh, t;
	};
}
