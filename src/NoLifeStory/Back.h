////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Back {
	public:
		void Draw();
		static void Load(Node n);
		AniSprite aspr;
		Sprite spr;
		int x, y, z;
		int rx, ry;
		int cx, cy;
		int type;
		int movetype;
		double movew, moveh, movep, mover;
		bool repeat;
		bool f;
		bool ani;
		static set <Back*> Backs;
	};
};