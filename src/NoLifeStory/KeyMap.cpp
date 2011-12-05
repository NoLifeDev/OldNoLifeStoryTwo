////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

map <sf::Keyboard::Key, function<void()>> NLS::Key::Map;
bool NLS::Key::Left, NLS::Key::Right, NLS::Key::Up, NLS::Key::Down;

void NLS::Key::Init() {
	Set(sf::Keyboard::Escape, Func(window->Close));
	Set(sf::Keyboard::F, Func(ThisPlayer->MouseFly));
	Set(sf::Keyboard::Up, Func(ThisPlayer->UsePortal));
	Set(sf::Keyboard::LAlt, Func(ThisPlayer->Jump));
	Set(sf::Keyboard::RAlt, Func(ThisPlayer->Jump));
	Set(sf::Keyboard::F1, [](){ThisPlayer->ChangeEmote(1);});
	Set(sf::Keyboard::F2, [](){ThisPlayer->ChangeEmote(2);});
	Set(sf::Keyboard::F3, [](){ThisPlayer->ChangeEmote(3);});
	Set(sf::Keyboard::F4, [](){ThisPlayer->ChangeEmote(4);});
	Set(sf::Keyboard::F5, [](){ThisPlayer->ChangeEmote(5);});
	Set(sf::Keyboard::F6, [](){ThisPlayer->ChangeEmote(6);});
	Set(sf::Keyboard::F7, [](){ThisPlayer->ChangeEmote(7);});
	Set(sf::Keyboard::F8, [](){ThisPlayer->ChangeEmote(8);});
	Set(sf::Keyboard::F9, [](){ThisPlayer->ChangeEmote(9);});
	Set(sf::Keyboard::F10, [](){ThisPlayer->ChangeEmote(10);});
	Set(sf::Keyboard::F11, [](){ThisPlayer->ChangeEmote(11);});
	Set(sf::Keyboard::F12, [](){ThisPlayer->ChangeEmote(12);});
	Set(sf::Keyboard::Num1, [](){ThisPlayer->ChangeEmote(13);});
	Set(sf::Keyboard::Num2, [](){ThisPlayer->ChangeEmote(14);});
	Set(sf::Keyboard::Num3, [](){ThisPlayer->ChangeEmote(15);});
	Set(sf::Keyboard::Num4, [](){ThisPlayer->ChangeEmote(16);});
	Set(sf::Keyboard::Num5, [](){ThisPlayer->ChangeEmote(17);});
	Set(sf::Keyboard::Num6, [](){ThisPlayer->ChangeEmote(18);});
	Set(sf::Keyboard::Num7, [](){ThisPlayer->ChangeEmote(19);});
	Set(sf::Keyboard::Num8, [](){ThisPlayer->ChangeEmote(20);});
	Set(sf::Keyboard::Num9, [](){ThisPlayer->ChangeEmote(21);});
	Set(sf::Keyboard::Num0, [](){ThisPlayer->ChangeEmote(22);});
	Left = Right = Up = Down = false;
}

void NLS::Key::Set(sf::Keyboard::Key k, function<void()> f) {
	Map[k] = f;
}
void NLS::Key::Handle(sf::Event e) {
	if (UI::TextBox::Active)
	switch (e.Type) {
	case sf::Event::KeyPressed:
		switch (e.Key.Code) {
		case sf::Keyboard::Return:
			if (e.Key.Alt) {
				Fullscreen = !Fullscreen;
				Config::Save();
				Graphics::Init();
			} else {
				UI::TextBox::Active->Send();
				UI::TextBox::Active = nullptr;
			}
			break;
		case sf::Keyboard::Delete:
		case sf::Keyboard::Back:
			if (UI::TextBox::Active) {
				UI::TextBox::Active->HandleKey(e.Key.Code);
			}
			break;
		case sf::Keyboard::Escape:
			UI::TextBox::Active = nullptr;
			break;
		}
		break;
	case sf::Event::TextEntered:
		UI::TextBox::Active->HandleChar(e.Text.Unicode);
		break;
	}
	else
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
			break;
		case sf::Keyboard::Left:
			if (!UI::TextBox::Active) 
				Left = true;
			else
				UI::TextBox::Active->HandleKey(e.Key.Code);
			break;
		case sf::Keyboard::Right:
			if (!UI::TextBox::Active) 
				Right = true;
			else
				UI::TextBox::Active->HandleKey(e.Key.Code);
			break;
		case sf::Keyboard::Up:
			if (!UI::TextBox::Active) 
				Up = true;
			else
				UI::TextBox::Active->HandleKey(e.Key.Code);
			break;
		case sf::Keyboard::Down:
			if (!UI::TextBox::Active) 
				Down = true;
			else
				UI::TextBox::Active->HandleKey(e.Key.Code);
			break;
		}
		if (UI::Focused)
		if (UI::Window::All.back()->HandleKey(e.Key.Code) or UI::Window::All.back()->stealsfocus) return;
		if (!Map::Login and Map[e.Key.Code]) Map[e.Key.Code]();
		break;
	case sf::Event::KeyReleased:
		switch (e.Key.Code) {
		case sf::Keyboard::Left:
			Left = false;
			break;
		case sf::Keyboard::Right:
			Right = false;
			break;
		case sf::Keyboard::Up:
			Up = false;
			break;
		case sf::Keyboard::Down:
			Down = false;
			break;
		}
		break;
	}
}