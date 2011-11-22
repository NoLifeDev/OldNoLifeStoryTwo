////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace View {
		extern int x, y;
		extern double vx, vy;
		extern double tx, ty;
		extern int xmin, xmax, ymin, ymax;
		extern int width, height;
		extern bool relative;
		void Init();
		void Step();
		void Reset();
	}
}
