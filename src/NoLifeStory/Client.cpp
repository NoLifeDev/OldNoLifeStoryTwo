////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Mindfuck = false;
float bgVolume;

void NLS::Init() {
	Time::Reset();
	locale::global(locale(""));
	freopen("nolifestory.log", "a", stdout);
	freopen("nolifestory.log", "a", stderr);
	cout << endl << "Initializing NoLifeStory" << endl;
	cout << "아무 라이프 스토리 없음" << endl;
	cout << "유니 코드는 사용" << endl;
	cout << "Using locale: " << locale().name() << endl;
	srand(time(0));
	Config::Load();
	Crypto::Init();
	InitWZ();
	Network::Init();
	Graphics::Init();
#ifdef NLS_WINDOWS
	BASS_Init(-1, 44100, 0, window->GetSystemHandle(), 0);
#else
	BASS_Init(-1, 44100, 0, (void*)window->GetSystemHandle(), 0);
#endif
	if (Mindfuck) {
		HSTREAM s = BASS_StreamCreateFile(false, "bgm.mp3", 0, 0, BASS_SAMPLE_FLOAT|BASS_SAMPLE_LOOP);
		BASS_ChannelPlay(s, true);
	}
	Text::Init();
	ThisPlayer = new _ThisPlayer;
	View::Init();
	Mouse::Init();
	UI::Init();
	Physics::Init();
	Key::Init();
	Time::Step();
	cout << "Initialization complete" << endl;
	MainChat << Text::Color(255, 255, 0, 255) << "[NoLifeStory] Welcome to NoLifeStory!" << cendl;
	if (NLS::Network::Online) {
		string v1 = NLS::Network::Version/100?tostring(NLS::Network::Version/100):string();
		string v2 = tostring(NLS::Network::Version%100);
		MainChat << Text::Color(255, 20, 50) << "[INFO] Connected with MapleStory v" + v1 + "." + v2 + "!" << cendl;
	} else {
		MainChat << Text::Color(255, 20, 50) << "[INFO] Not connected with any MapleStory server!" << cendl;
	}
	Map::Load("100000000", "");
	Map::Load();
}

bool NLS::Loop() {
	sf::Event e;
	while (window->PollEvent(e)) {
		switch (e.Type) {
		case sf::Event::TextEntered:
		case sf::Event::KeyPressed:
			Key::Handle(e);
			break;
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseWheelMoved:
			Mouse::HandleEvent(e);
			break;
		case sf::Event::Closed:
			return false;
			break;
		case sf::Event::LostFocus:
			bgVolume = NLS::Map::bgmusic.GetVolume();
			NLS::Map::bgmusic.SetVolume(0);
			break;
		case sf::Event::GainedFocus:
			NLS::Map::bgmusic.SetVolume(bgVolume);
			break;
		default:
			break;
		}
	}
	Graphics::Draw();
	if (!Map::nextmap.empty()) {
		Map::Load();
	}
	Network::Loop();
	return window->IsOpened();
}

void NLS::Unload() {
	Text::Unload();
	window->Close();
	BASS_Free();
}
