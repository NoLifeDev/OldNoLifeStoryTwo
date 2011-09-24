////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Console* NLS::console;

NLS::Console::Console() {
	shutdown = false;
	toggle = false;
	show = true;
#ifdef VS11
	t = new thread([&](){this->Loop();});
#else
	t = new sf::Thread([&](){this->Loop();});
	t->Launch();
#endif
}

void NLS::Console::Loop() {
	file.open("console.log");
	window = new sf::RenderWindow(sf::VideoMode(400,400,32), "NoLifeStory::FancyConsole", sf::Style::Resize|sf::Style::Close, sf::ContextSettings(0, 0, 0, 2, 0));
	window->Show(show);
#ifdef NLS_WINDOWS
	HANDLE hIcon = LoadIconW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(IDI_NOLIFESTORY_ICON));
	HWND hWnd = window->GetSystemHandle();
	if (hWnd) {
		::SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
	}
#endif
	font = new sf::Font();
#ifdef NLS_WINDOWS
	auto bleh1 = FindResource(0, MAKEINTRESOURCE(IDI_NOLIFESTORY_FONT), MAKEINTRESOURCE(RT_RCDATA));
	auto bleh2 = LoadResource(0, bleh1);
	font->LoadFromMemory(LockResource(bleh2), SizeofResource(0, bleh1));
#else
	font->LoadFromFile("font.ttf");
#endif
	pos = 0;
	while (!shutdown) {
		if (toggle) {
			window->Show(show);
			toggle = false;
		}
		sf::Event e;
		while (window->PollEvent(e)) {
			switch (e.Type) {
			case sf::Event::KeyPressed:
				switch (e.Key.Code) {
				case sf::Keyboard::Back:
					if (pos != 0) {
						str.erase(--pos, 1);
					}
					break;
				case sf::Keyboard::Delete:
					if (pos != str.size()) {
						str.erase(pos, 1);
					}
					break;
				case sf::Keyboard::Left:
					pos = max<int32_t>(0, pos-1);
					break;
				case sf::Keyboard::Right:
					pos = min<int32_t>(str.size(), pos+1);
					break;
				case sf::Keyboard::Return:
					Push(str);
					HandleCommand(str);
					str.clear();
					pos = 0;
					break;
				case sf::Keyboard::Tilde:
					Toggle();
					break;
				}
				break;
			case sf::Event::TextEntered:
				if (e.Text.Unicode != 13 and e.Text.Unicode != 8 and e.Text.Unicode != 96 and e.Text.Unicode != 27) {
					str.insert(pos++, 1, e.Text.Unicode);
				}
				break;
			case sf::Event::Closed:
				show = false;
				toggle = true;
				break;
			case sf::Event::Resized:
				window->SetView(sf::View(sf::FloatRect(0, 0, window->GetWidth(), window->GetHeight())));
				break;
			}
		}
		window->Clear();
		sf::Text t(str, *font, 8);
		t.SetPosition(0, window->GetHeight()-10);
		window->Draw(t);
#ifdef VS11
		m.lock();
#else
		m.Lock();
#endif
		for (int i = 0; i < strs.size(); i++) {
			sf::Text t(strs[strs.size()-i-1], *font, 8);
			t.SetPosition(0, window->GetHeight()-12*i-24);
			window->Draw(t);
			if (window->GetHeight()-12*i-24 < 0) {
				break;
			}
		}
#ifdef VS11
		m.unlock();
#else
		m.Unlock();
#endif
		sf::Shape s = sf::Shape::Line(0, window->GetHeight()-12, window->GetWidth(), window->GetHeight()-12, 1, sf::Color::White);
		window->Draw(s);
		window->Display();
		if (show) {
			sf::Sleep(max(50-(int)window->GetFrameTime(), 0));
		} else {
			sf::Sleep(max(1000-(int)window->GetFrameTime(), 0));
		}
	}
	delete font;
	delete window;
}

void NLS::Console::HandleCommand(const string& str) {
	istringstream iss(str);
	vector<string> command;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string>>(command));
	if (command.size() == 0) {
		return;
	}
	if (command[0] == "help" or command[0] == "?") {
		if (command.size() == 1) {
			Push("Available commands:");
			Push("help [Command Name]");
			Push("? [Command Name]");
			Push("exit");
			Push("load <Map ID> [Portal ID]");
		} else {
			if (command[1] == "help" or command[1] == "?") {
				Push("help [Command Name]");
				Push("Provides information on what commands are available and what they do");
				Push("? is a synonym for help");
			} else if (command[1] == "exit") {
				Push("exit");
				Push("Aborts NoLifeStory");
			} else if (command[1] == "load") {
				Push("load <Map ID> [Portal ID]");
				Push("Loads the specified map and also optionally navigates to the specified portal.");
			} else {
				Push("Unknown command "+command[1]);
			}
		}
	} else if (command[0] == "exit") {
		exit(0);
	} else if (command[0] == "load") {
		if (command.size() == 1) {
			Push("Please specify a map id when using the load command");
		} else if (command.size() == 2) {
			Map::Load(command[1], "");
		} else {
			Map::Load(command[1], command[2]);
		}
	} else {
		Push("Unknown command!");
	}
}

void NLS::Console::Push(const string& str) {
#ifdef VS11
		m.lock();
#else
		m.Lock();
#endif
	file << str << endl;
	strs.push_back(str);
	file.flush();
#ifdef VS11
		m.unlock();
#else
		m.Unlock();
#endif
}

void NLS::Console::Toggle() {
	show = !show;
	toggle = true;
}

NLS::Console::~Console() {
	shutdown = true;
#ifdef VS11
	t->join();
#else
	t->Wait();
#endif
	delete t;
}