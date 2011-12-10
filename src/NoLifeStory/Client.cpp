////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Mindfuck = false;
bool NLS::bMute = false;
float bgVolume;

void NLS::Init() {
	Time::Reset();
	Config::Load();
	locale::global(locale(""));
#ifndef _DEBUG
	// Log output to logfile
	freopen("nolifestory.log", "a", stdout);
	freopen("nolifestory.log", "a", stderr);
#endif
	cout << endl << "Initializing NoLifeStory" << endl;
	cout << "아무 라이프 스토리 없음" << endl;
	cout << "유니 코드는 사용" << endl;
	cout << "Using locale: " << locale().name() << endl;

	srand(time(0));

	auto initDone = [](const string &msg) { cout << "[Loading] Init " << msg << " done." << endl; };

	Crypto::Init();
	initDone("Cryptography");

	InitWZ();
	initDone("WZ data");

	Network::Init();
	initDone("Network");

	Graphics::Init();
	initDone("Graphics");

#ifdef NLS_WINDOWS
	BASS_Init(-1, 44100, 0, window->GetSystemHandle(), 0);
#else
	BASS_Init(-1, 44100, 0, (void*)window->GetSystemHandle(), 0);
#endif
	initDone("BASS Sound System");

	if (Mindfuck) {
		HSTREAM s = BASS_StreamCreateFile(false, "bgm.mp3", 0, 0, BASS_SAMPLE_FLOAT|BASS_SAMPLE_LOOP);
		BASS_ChannelPlay(s, true);
	}

	Text::Init();
	initDone("Text");

	Player::Init();
	ThisPlayer = new _ThisPlayer;
	initDone("Player Data");

	View::Init();
	initDone("View");

	Mouse::Init();
	initDone("Mouse");

	UI::Init();
	initDone("User Interface");

	Physics::Init();
	initDone("Physics System");

	Key::Init();
	initDone("AES Keys");

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
	if (Profiling) {
		cout << "Running in profiling mode. Have fun!" << cendl;
		Node n = WZ["Map"]["Map"];
		for (int i = 0; i < 10; i++) {
			Node nn = n["Map"+tostring(i)];
			if (nn)
			for_each(nn.begin(), nn.end(), [](pair<string, Node> p){
				ProfileMaps.push_back(p.first);
			});
		}
	}
	if (Network::Online) Map::Load("MapLogin", "");
	else Map::Load("100000000", "");
	Map::Load();
}

bool NLS::Loop() {
	sf::Event e;
	while (window->PollEvent(e)) {
		switch (e.Type) {
		case sf::Event::TextEntered:
		case sf::Event::KeyPressed:
		case sf::Event::KeyReleased:
			Key::Handle(e);
			break;
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
		case sf::Event::MouseWheelMoved:
		case sf::Event::MouseMoved:
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
			if(bMute) {
				NLS::Map::bgmusic.SetVolume(0);
			} else {
				NLS::Map::bgmusic.SetVolume(bgVolume);
			}
			break;
		default:
			break;
		}
	}
	Graphics::Draw();
	if (Profiling) {
		if (ProfileMaps.empty()) return false;
		Map::Load(ProfileMaps.back(), "");
		ProfileMaps.pop_back();
		Map::Load();
	}
	else
	if (!Map::nextmap.empty() and Map::fade < 0) {
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
