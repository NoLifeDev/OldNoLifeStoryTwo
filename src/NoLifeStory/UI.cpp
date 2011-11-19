////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

string chat;//Temporary
bool enteringtext = false;
bool justentered = false;

void NLS::UI::Init() {
	
}
void NLS::UI::Draw() {
	if (enteringtext) {
		glColor4f(1, 1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(800, 0);
		glVertex2i(800, 20);
		glVertex2i(0, 20);
		glEnd();
		Text t(chat, 14);
		t.Draw(2, 2);
	}
}

bool NLS::UI::HandleKey(sf::Keyboard::Key key) {
	if (enteringtext) {
		return true;
	}
	switch (key) {
	case sf::Keyboard::Return:
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::LAlt) or sf::Keyboard::IsKeyPressed(sf::Keyboard::RAlt)) {
			Fullscreen = !Fullscreen;
			Config::Save();
			Graphics::Init();
		} else if (!enteringtext) {
			enteringtext = true;
			justentered = true;
		}
		return true;
		break;
	case sf::Keyboard::Escape:
		return false;
		break;
	default:
		return false;
	}
}
void NLS::UI::HandleChar(uint32_t ch) {
	if (!enteringtext) return;
	switch (ch) {
	case 0x8:
		chat.erase(chat.size()-1);
		return;
	case 0xA:
	case 0xD:
		if (justentered) {
			justentered = false;
			return;
		}
		enteringtext = false;
		Map::Load(chat, "");
		chat = "";
		return;
	case 0x1B:
		enteringtext = false;
		return;
	}
	static char s[4];
	char* ss = sf::Utf8::Encode(ch, s);
	chat.append(s, ss-s);
}
bool NLS::UI::HandleMousePress(sf::Mouse::Button, int, int) {
	return false;
}
bool NLS::UI::HandleMouseRelease(sf::Mouse::Button, int, int) {
	return false;
}
bool NLS::UI::HandleMouseScroll(int, int, int) {
	return false;
}