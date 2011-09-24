////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

//#define PROFILING
#ifdef PROFILING
string maps[] = {"100000000", "200000000", "300000000", "600000000"};
#endif

void NLS::Init(const vector<string>& args) {
	C("INFO") << "Initializing NoLifeStory" << endl;
	Network::Init();
	Time.Reset();
	WZ::Init(args.size()>1?args[1]:"");
	Time.Step();
	Graphics::Init();
	BASS_Init(-1, 44100, 0, window->GetSystemHandle(), 0);
	Map::Load("100000000", "");
	Map::Load();
}

bool NLS::Loop() {
	sf::Event e;
	while (window->PollEvent(e)) {
		switch (e.Type) {
		case sf::Event::KeyPressed:
			switch (e.Key.Code) {
			case sf::Keyboard::Tilde:
				console->Toggle();
				break;
			case sf::Keyboard::Escape:
				return false;
			}
			break;
		case sf::Event::Closed:
			return false;
			break;
		}
	}
	Graphics::Draw();
#ifdef PROFILING
	static int i(0);
	if (i>4) {
		return false;
	}
	Map::Load(maps[i++], "");
#endif
	if (!Map::nextmap.empty()) {
		Map::Load();
	}
	return true;
}

void NLS::Unload() {
	BASS_Free();
}