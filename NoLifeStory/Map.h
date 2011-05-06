///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace Map {
	void Load(string id, string portal);
	extern string nextmap;
	extern string nextportal;
	extern string currentmap;
	extern int currentLoginStep;
	extern wz::node node;
	void Load();
	void LoadFoothold();
	void LoadLadder();
	void LoadTile();
	void LoadPortal();
	void LoadObj();
	void LoadBack();
	void LoadLife();
	void ChangeLoginStep(int8_t step);
	void GenerateMapDimensions();
};