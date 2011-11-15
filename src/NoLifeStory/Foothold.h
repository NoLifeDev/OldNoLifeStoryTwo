////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Foothold {
	public:
		double x1, y1, x2, y2;
		double dir, len;
		double force;
		Foothold *next, *prev;
		int id, nextid, previd;
		int layer, group;
		bool forbid;
		bool walk;
		static void Load(Node n);
		static void Draw();
		static set<Foothold*> All;
		static set<Foothold*>::iterator begin() {return All.begin();}
		static set<Foothold*>::iterator end() {return All.end();}
	};
}
