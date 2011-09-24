////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class AniSprite {
	public:
		AniSprite();
		void Set(class Node n);
		void Draw(int x, int y, bool flipped = false, float rotation = 0);
		void Step();
		Node n, f;
		int delay;
		int frame;
		bool repeat;
		float a;
	};
}