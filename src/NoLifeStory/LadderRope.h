////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class LadderRope {
	public:
		double x, y1, y2;
		int page;
		bool l, uf;
		static void Load(Node n);
		static void Draw();
		static set<LadderRope*> All;
		static set<LadderRope*>::iterator begin() {return All.begin();}
		static set<LadderRope*>::iterator end() {return All.end();}
	};
}