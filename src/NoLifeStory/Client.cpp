////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

//#define PROFILING
#ifdef PROFILING
string maps[] = {"1000000", "2000000", "100000000", "101000000", "102000000", "103000000", "104000000", "105000000", "106000000", "107000000", "110000000", "120000000", "130000000", "140000000", "180000000", "190000000", "191000000", "192000000", "193000000", "195000000", "196000000", "197000000", "199000000", "200000000", "200100000", "209000000", "211000000", "220000000", "221000000", "222000000", "230000000", "240000000", "250000000", "251000000", "260000000", "261000000", "270000000", "271000000", "300000000", "310000000", "390000000", "540000000", "541000000", "550000000", "551000000", "555000000", "600000000", "680000000", "681000000", "682000000", "683000000", "684000000", "800000000", "801000000"};
#endif

void NLS::Init(const vector<string>& args) {
	freopen("nolifestory.log", "a", stdout);
	freopen("nolifestory.log", "a", stderr);
	cout << "Initializing NoLifeStory" << endl;
	srand(time(0));
	Network::Init();
	Time.Reset();
	InitWZ(args.size()>1?args[1]:"");
	Time.Step();
	Graphics::Init();
	Physics::Init();
#ifdef NLS_WINDOWS
	BASS_Init(-1, 44100, 0, window->GetSystemHandle(), 0);
#else
	BASS_Init(-1, 44100, 0, (void*)window->GetSystemHandle(), 0);
#endif
	cout << "Initialization complete" << endl;
	Map::Load("0", "");
	Map::Load();
}

bool NLS::Loop() {
	sf::Event e;
	while (window->PollEvent(e)) {
		switch (e.Type) {
		case sf::Event::KeyPressed:
			if (UI::HandleKeyPress(e.Key.Code)) {
				break;
			}
			switch (e.Key.Code) {
			case sf::Keyboard::Escape:
				return false;
				break;
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			if (UI::HandleKeyRelease(e.Key.Code)) {
				break;
			}
			switch (e.Key.Code) {
			default:
				break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (UI::HandleMousePress(e.MouseButton.Button, e.MouseButton.X, e.MouseButton.Y)) {
				break;
			}
			//TODO - Handle clicking on npcs and mobs and other players and stuff.
			break;
		case sf::Event::MouseButtonReleased:
			UI::HandleMouseRelease(e.MouseButton.Button, e.MouseButton.X, e.MouseButton.Y);
			break;
		case sf::Event::MouseWheelMoved:
			UI::HandleMouseScroll(e.MouseWheel.Delta, e.MouseButton.X, e.MouseButton.Y);
		case sf::Event::Closed:
			return false;
			break;
		default:
			break;
		}
	}
	Graphics::Draw();
#ifdef PROFILING
	static int i(0);
	if (i>=54) {
		return false;
	}
	Map::Load(maps[i++], "");
#endif
	if (!Map::nextmap.IsEmpty()) {
		Map::Load();
	}
	return true;
}

void NLS::Unload() {
	window->Close();
	BASS_Free();
}
