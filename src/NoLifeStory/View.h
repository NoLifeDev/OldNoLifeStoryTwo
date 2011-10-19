////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class _View {
	public:
		int x, y;
		double vx, vy;
		double tx, ty;
		int xmin, xmax, ymin, ymax;
		int width, height;
		bool relative;
		void Step();
		void Reset();
		_View();
	} extern View;
};