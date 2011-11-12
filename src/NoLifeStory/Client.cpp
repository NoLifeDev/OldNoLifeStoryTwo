////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

//#define PROFILING
void NLS::Init(const vector<string>& args) {
	locale::global(locale(""));
	freopen("nolifestory.log", "a", stdout);
	freopen("nolifestory.log", "a", stderr);
	cout << endl << "Initializing NoLifeStory" << endl;
	cout << "아무 라이프 스토리 없음" << endl;
	cout << "유니 코드는 사용" << endl;
	cout << "Using locale: " << locale().name() << endl;
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
	KeySet(sf::Keyboard::Escape, Func(window->Close));
	KeySet(sf::Keyboard::F, Func(ThisPlayer.MouseFly));
	KeySet(sf::Keyboard::Up, Func(ThisPlayer.UsePortal));
	KeySet(sf::Keyboard::LAlt, Func(ThisPlayer.Jump));
	KeySet(sf::Keyboard::RAlt, Func(ThisPlayer.Jump));
	cout << "Initialization complete" << endl;
	Map::Load("100000000", "");
	Map::Load();
}

bool NLS::Loop() {
	if (NLS::Network::Online) {
		Network::Loop();
	}
	sf::Event e;
	while (window->PollEvent(e)) {
		switch (e.Type) {
		case sf::Event::KeyPressed:
			if (UI::HandleKey(e.Key.Code)) {
				break;
			}
			KeyMap[e.Key.Code]();
			break;
			//TODO - Pass all these events to the Cursor and let that handle stuff.
		case sf::Event::MouseButtonPressed:
			if (UI::HandleMousePress(e.MouseButton.Button, e.MouseButton.X, e.MouseButton.Y)) {
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			UI::HandleMouseRelease(e.MouseButton.Button, e.MouseButton.X, e.MouseButton.Y);
			break;
		case sf::Event::MouseWheelMoved:
			UI::HandleMouseScroll(e.MouseWheel.Delta, e.MouseButton.X, e.MouseButton.Y);
			break;
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
	if (!Map::nextmap.empty()) {
		Map::Load();
	}
	return window->IsOpened();
}

void NLS::Unload() {
	window->Close();
	BASS_Free();
}
