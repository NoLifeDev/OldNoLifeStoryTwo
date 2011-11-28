////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

map <sf::Keyboard::Key, NLS::Key::Action> NLS::Key::Map;
bool Left, Right, Up, Down;

void NLS::Key::Init() {
	Set(sf::Keyboard::Escape, Func(window->Close));
	Set(sf::Keyboard::F, Func(ThisPlayer->MouseFly));
	Set(sf::Keyboard::Up, Func(ThisPlayer->UsePortal));
	Set(sf::Keyboard::LAlt, Func(ThisPlayer->Jump));
	Set(sf::Keyboard::RAlt, Func(ThisPlayer->Jump));
}

NLS::Key::Action::Action() {
	action = 0;
}
NLS::Key::Action::Action(function<void()> f) {
	action = f;
}
void NLS::Key::Set(sf::Keyboard::Key k, function<void()> f) {
	Map[k] = f;
}
void NLS::Key::Handle(sf::Event e) {
	switch (e.Type) {
	case sf::Event::KeyPressed:
		switch (e.Key.Code) {
		case sf::Keyboard::Return:
			if (e.Key.Alt) {
				Fullscreen = !Fullscreen;
				Config::Save();
				Graphics::Init();
				return;
			}
			if (UI::TextBox::Active) {
				UI::TextBox::Active->Send();
				return;
			}
			break;
		case sf::Keyboard::Escape:
			if (UI::TextBox::Active) {
				UI::TextBox::Active = nullptr;
				return;
			}
			break;
		}
		if (UI::Focused) {
			UI::Window::All.back()->HandleKey(e.Key.Code);
			return;
		}
		Map[e.Key.Code]();
		break;
	case sf::Event::TextEntered:
		if (UI::TextBox::Active) {
			UI::TextBox::Active->HandleChar(e.Text.Unicode);
		}
		break;
	}
}