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
		bool relative;
		int width, height;
		void Step();
		void Reset();
		_View();
	} extern View;
};