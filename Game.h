///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

extern double delta;
extern double tdelta;
extern bool mindfuck;
extern Timer nlstime;
extern double loadtime;
extern double alpha;
extern sound music;
extern bool resort;
extern this_player *theplayer;
namespace Game {
	//extern string curMap;
	//extern wz::node curMapNode;
	bool init(string* argv, int argc);
	bool loop();
	void handle_input();
	void unload();
	extern bool DevPortals;
	extern bool Running;

	enum RenderMode {
		NORMAL,
		FADEIN,
		FADED,
		FADEOUT
	};

	extern RenderMode Mode;
}