////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::UI::Element NLS::UI::Screen;
NLS::UI::TextBox* NLS::UI::TextBox::Active = nullptr;

void NLS::UI::Init() {
	Screen.x = 0;
	Screen.y = 0;
	Screen.width = View::width;
	Screen.height = View::height;
	/*
	NLS::UI::Window *window = new NLS::UI::Window();
	NLS::Sprite sprite = WZ["UI"]["StatusBar"]["base"]["backgrnd"];
	window->setBackground(sprite);
	window->setX(0);
	window->setY(600 - sprite.data->height);
	window->setDragable(false);
	window->setVisible(true);
	window->setEnabled(true);
	AddWindow(window, 1);

	window = new NLS::UI::Window();
	sprite = WZ["UI"]["StatusBar"]["base"]["backgrnd2"];
	window->setBackground(sprite);
	window->setX(2);
	window->setY(600 - sprite.data->height);
	window->setDragable(false);
	window->setVisible(true);
	window->setEnabled(true);

	// Generate the level thingy

	NLS::Node sprites = WZ["UI"]["Basic"]["LevelNo"]; // numbers
	int level1 = NLS::ThisPlayer.level / 100;
	int level2 = NLS::ThisPlayer.level / 10 - level1 * 10;
	int level3 = NLS::ThisPlayer.level % 10;
	NLS::UI::Image *img;

	img = new NLS::UI::Image();
	img->setSprite(sprites["blank"]);
	img->setX(38);
	img->setY(47);
	window->addChild(img);

	img = new NLS::UI::Image();
	img->setSprite(sprites["blank"]);
	img->setX(50);
	img->setY(47);
	window->addChild(img);

	img = new NLS::UI::Image();
	img->setSprite(sprites["blank"]);
	img->setX(62);
	img->setY(47);
	window->addChild(img);
	
	if (level1 > 0) {
		img = new NLS::UI::Image();
		img->setSprite(sprites[tostring(level1)]);
		img->setX(38);
		img->setY(47);
		window->addChild(img);
	}
	
	if (level2 > 0) {
		img = new NLS::UI::Image();
		img->setSprite(sprites[tostring(level2)]);
		img->setX(50);
		img->setY(47);
		window->addChild(img);
	}

	img = new NLS::UI::Image();
	img->setSprite(sprites[tostring(level3)]);
	img->setX(62);
	img->setY(47);
	window->addChild(img);

	AddWindow(window, 1);
}

void NLS::UI::AddWindow(NLS::UI::Window *window, int32_t layer) {
	windows[layer].push_back(window);
}

void NLS::UI::Draw() {
	for (int32_t layerI = 4; layerI > 0; layerI--) {
		for (size_t i = 0; i < windows[layerI].size(); i++) {
			windows[layerI][i]->Draw();
		}
	}

	if (enteringtext) {
		carretFlicker++;
		if (carretFlicker >= 100) {
			carretFlicker = 0;
		}

		// Get box length
		int8_t textLineHeight = 20; // 20 pixels per line
		int32_t boxLength = 0;
		boxLength += maxLinesShown * textLineHeight;

		// Draw box
		glColor4f(0.8f, 0.8f, 0.8f, 0.75f);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);

		// TODO: Add width and height from static values
		glVertex2i(0, 0);
		glVertex2i(800, 0);
		glVertex2i(800, boxLength);
		glVertex2i(0, boxLength);
		glEnd();
		// End draw box

		// Draw chatlog
		int32_t curPos = 2;
		for (size_t i = chatlogCurrentTopmostLine; i < chatlog.size() && i < chatlogCurrentTopmostLine + maxLinesShown; i++) {
			chatlog[i].Draw(2, curPos);
			curPos += textLineHeight;
		}
			

		{
			// draw fancy bar.
			glColor4f(0.2f, 0.2f, 0.2f, 1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBegin(GL_QUADS);
			glVertex2i(790, 0);
			glVertex2i(800, 0);
			glVertex2i(800, boxLength);
			glVertex2i(790, boxLength);
			glEnd();

			float lineHeight = (float)boxLength / (float)(chatlog.size() < maxLinesShown ? 5 : chatlog.size());

			float minY = chatlogCurrentTopmostLine * lineHeight;
			float maxY = (chatlogCurrentTopmostLine + maxLinesShown) * lineHeight;
			if (maxY > boxLength) {
				maxY = boxLength;
			}

			glColor4f(0.4f, 0.4f, 0.4f, 1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBegin(GL_QUADS);
			glVertex2i(790, minY);
			glVertex2i(800, minY);
			glVertex2i(800, maxY);
			glVertex2i(790, maxY);
			glEnd();
		}
		
		glColor4f(0.9f, 0.9f, 0.9f, 1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);

		// TODO: Add width and height from static values
		glVertex2i(0, boxLength);
		glVertex2i(800, boxLength);
		glVertex2i(800, boxLength + textLineHeight);
		glVertex2i(0, boxLength + textLineHeight);
		glEnd();

		Text t(chat, 14);
		t.Draw(2, boxLength + 2);

		if (carretFlicker < 50) {
			glColor4f(0, 0, 0, 1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBegin(GL_QUADS);
			int32_t w = t.Width();
			int32_t h = t.Height();
			glVertex2i(3 + w, boxLength + 2);
			glVertex2i(4 + w, boxLength + 2);
			glVertex2i(4 + w, boxLength + 2 + h);
			glVertex2i(3 + w, boxLength + 2 + h);
			glEnd();
		}
	}
}

bool NLS::UI::HandleKey(sf::Event _event) {
	sf::Keyboard::Key key = _event.Key.Code;
	if (enteringtext) {
		switch (key) {
		case sf::Keyboard::Up:
			if (chatlogCurrentTopmostLine > 0) {
				chatlogCurrentTopmostLine--;
			}
			break;
		case sf::Keyboard::Down:
			if (chatlogCurrentTopmostLine < chatlog.size() - maxLinesShown) {
				chatlogCurrentTopmostLine++;
			}
			break;
		case sf::Keyboard::V: {
			if (_event.Key.Control) {
				string text = GetClipboardText();
				for (size_t i = 0; i < text.size(); i++) {
					HandleChar((uint32_t)text[i]);
				}
			}
			break;
			}
		}

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
	case 0x16: return; // CTRL + V charcode... not needed!
	case 0x8:
		if (!chat.size()) return;
		chat.erase(chat.size()-1);
		return;
	case 0xA:
	case 0xD:
		if (justentered) {
			justentered = false;
			return;
		}
		enteringtext = false;
		if (chat.length() == 0) return;

		AddChatlog(chat);

		if (chat.length() <= 9) {
			Map::Load(chat, "");
		}
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

void NLS::UI::Window::Draw() {
	if (!isVisible()) return;
	background.Draw(getViewX(), getViewY());
	for (size_t i = 0; i < children.size(); i++) {
		children[i]->Draw();
	}
}

void NLS::UI::Window::setBackground(NLS::Sprite bg) {
	setWidth(bg.data->width);
	setHeight(bg.data->height);
	background = bg;
}

void NLS::UI::Image::Draw() {
	if (!isVisible()) return;
	sprite.Draw(getViewX(), getViewY());
}

void NLS::UI::AnimatedImage::Draw() {
	if (!isVisible()) return;
	sprite.Draw(getViewX(), getViewY());
}
*/