////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Map {
		void Load(const string& id, const string& portal);
		void Load();
		void Draw();
		void DrawClock();
		Player * GetPlayer(uint32_t);
		extern Node node;
		extern string nextmap;
		extern string nextportal;
		extern int8_t nextportalID;
		extern string curmap;
		class Layer {
		public:
			void Draw();
			vector<Obj*> Objs;
			vector<Tile*> Tiles;
		};
		extern vector<Back*> Backgrounds;
		extern Layer Layers[8];
		extern vector<Back*> Foregrounds;
		extern map<uint32_t, Player*> Players;
		extern Sound bgmusic;
		extern float fade;
		extern bool Login;
		//extern Text scrollingHeader;
	}
}
