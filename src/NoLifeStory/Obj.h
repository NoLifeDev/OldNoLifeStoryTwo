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
		bool repeat;
		int movetype;
		double movew, moveh, movep, mover;
		bool flow;
		double rx, ry;
		bool f;
		AniSprite spr;
		static set <Obj*> Objs;
	};
};