////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Foothold {
	public:
		double x1, y1, x2, y2;
		double dir, len;
		Foothold *next, *prev;
		int id, nextid, previd;
		int layer, group;
		double force;
		bool forbid;
		bool walk;
		static void Load(Node n);
		static void Draw();
	};
	extern set <Foothold*> footholds;
};