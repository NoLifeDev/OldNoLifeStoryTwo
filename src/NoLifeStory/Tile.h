////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Tile {
	public:
		static void Load(Node n);
		void Draw();
		int x, y, z;
		Sprite spr;
		static set <Tile*> Tiles;
	};
};