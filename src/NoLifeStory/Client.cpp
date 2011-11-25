////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

bool NLS::Mindfuck = false;
float bgVolume;

void NLS::Init() {
	Time.Reset();
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
	Network::Init();
	InitWZ();

	if (Network::Version != NLS::Version) {
		cout << "[Warning] WZ files version (" << NLS::Version << ") is not the same as the server's (" << Network::Version << ")." << endl;
	}

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
	UI::Init();
	Mouse::Init();
	Text::Init();
	Physics::Init();
	KeySet(sf::Keyboard::Escape, Func(window->Close));
	KeySet(sf::Keyboard::F, Func(ThisPlayer.MouseFly));
	KeySet(sf::Keyboard::Up, Func(ThisPlayer.UsePortal));
	KeySet(sf::Keyboard::LAlt, Func(ThisPlayer.Jump));
	KeySet(sf::Keyboard::RAlt, Func(ThisPlayer.Jump));
	Time.Step();
	cout << "Initialization complete" << endl;
	NLS::UI::AddChatlog("[NoLifeStory] Welcome to NoLifeStory!", NLS::Text::TextColor(255, 255, 0));
	if (NLS::Network::Online) {
		string v1 = NLS::Network::Version / 100 != 0 ? tostring(((int32_t)NLS::Network::Version / 100)) : "";
		string v2 = tostring(NLS::Network::Version % 100);
		NLS::UI::AddChatlog("[INFO] Connected with MapleStory v" + v1 + "." + v2 + "!", NLS::Text::TextColor(255, 20, 50));
	}
	else {
		NLS::UI::AddChatlog("[INFO] Not connected with any MapleStory server!", NLS::Text::TextColor(255, 20, 50));
	}
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
		case sf::Event::TextEntered:
			UI::HandleChar(e.Text.Unicode);
			break;
		case sf::Event::KeyPressed:
			if (UI::HandleKey(e)) {
				break;
			}
			KeyMap[e.Key.Code]();
			break;
			//TODO - Pass all these events to the Cursor and let that handle stuff.
		case sf::Event::MouseButtonPressed:
			NLS::Mouse::Status = NLS::Mouse::OnOverClickableLocked;
			if (UI::HandleMousePress(e.MouseButton.Button, e.MouseButton.X, e.MouseButton.Y)) {
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			UI::HandleMouseRelease(e.MouseButton.Button, e.MouseButton.X, e.MouseButton.Y);
			NLS::Mouse::Status = NLS::Mouse::Normal;
			break;
		case sf::Event::MouseWheelMoved:
			UI::HandleMouseScroll(e.MouseWheel.Delta, e.MouseButton.X, e.MouseButton.Y);

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
		case sf::Event::MouseMoved:
			NLS::UI::HandleMouseMove(e.MouseMove.X, e.MouseMove.Y);
			NLS::Mouse::HandleMouseMove(e.MouseMove);
			break;
		default:
			break;
		}
	}
	Graphics::Draw();
	if (!Map::nextmap.empty()) {
		Map::Load();
	}
	return window->IsOpened();
}

void NLS::Unload() {
	Text::Unload();
	window->Close();
	BASS_Free();
}
