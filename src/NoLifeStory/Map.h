////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Map {
		void Load(const ustring& id, const ustring& portal);
		void Load();
		void Draw();
		extern Node node;
		extern ustring nextmap;
		extern ustring nextportal;
		extern ustring curmap;
		class Layer {
		public:
			void Draw();
			vector<Obj*> Objs;
			vector<Tile*> Tiles;
		};
		extern vector<Back*> Backgrounds;
		extern Layer Layers[8];
		extern vector<Back*> Foregrounds;
		extern Sound bgmusic;
	}
}
