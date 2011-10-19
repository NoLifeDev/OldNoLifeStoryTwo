////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Obj {
	public:
		void Draw();
		static void Load(Node n);
		int x, y, z;
		int movetype;
		double movew, moveh, movep, mover;
		double rx, ry;
		AniSprite spr;
		bool repeat, f, flow;
		static set <Obj*> Objs;
	};
}
