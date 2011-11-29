////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::UI::TextBox* NLS::UI::TextBox::Active = nullptr;
bool NLS::UI::Focused;
list<NLS::UI::Window*> NLS::UI::Window::All;

/*
namespace Functors {
	struct TestMessageBoxKeyHandler {
		bool operator()(NLS::UI::Element *elem, sf::Keyboard::Key key) {
			if (key == sf::Keyboard::Space) {
				elem->setVisible(false);
				NLS::UI::RemoveWindow((NLS::UI::Window *)elem);
				elem = nullptr;
				return true;
			}
			return false;
		}
	};
}
*/
void NLS::UI::Init() {
	
}
void NLS::UI::Draw() {
	for_each(Window::begin(), Window::end(), [](Window* w){
		w->Draw();
	});
}

void NLS::UI::Window::Draw() {
	for_each(Elements.begin(), Elements.end(), [&](Element* e){
		e->Draw();
	});
}

void NLS::UI::Window::Focus() {
	if (!focusable) return;
	if (All.back() == this) return;
	if (All.back()->stealsfocus) return;
	auto it = find(begin(), end(), this);
	if (it == end()) {
		cerr << "The UI is screwed up D:" << endl;
		throw(273);
	}
	All.erase(it);
	All.push_back(this);
}
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
	uint8_t level1 = NLS::ThisPlayer.level / 100;
	uint8_t level2 = NLS::ThisPlayer.level / 10 - level1 * 10;
	uint8_t level3 = NLS::ThisPlayer.level % 10;
	NLS::UI::Image *img;

	img = new NLS::UI::Image();
	img->setSprite(level1 > 0 ? sprites[tostring(level1)] : sprites["blank"]);
	img->setX(38);
	img->setY(47);
	window->addChild(img);

	img = new NLS::UI::Image();
	img->setSprite((level2 == 0 && level1 > 0) || (level2 > 0) ? sprites[tostring(level2)] : sprites["blank"]);
	img->setX(50);
	img->setY(47);
	window->addChild(img);

	img = new NLS::UI::Image();
	img->setSprite(sprites[tostring(level3)]);
	img->setX(62);
	img->setY(47);
	window->addChild(img);

	AddWindow(window, 1);

	auto msgBox = new Dialog();
	msgBox->SetImages(2);
	msgBox->AddMsg("Welkom op NoLifeStory!");
	msgBox->AddMsg("Gewoon space drukken hé!");
	msgBox->AddMsg("Gewoon space drukken hé!");
	msgBox->AddMsg("Gewoon space drukken hé!");
	msgBox->AddMsg("Gewoon space drukken hé!");
	msgBox->AddMsg("Gewoon space drukken hé!");
	msgBox->AddMsg("Gewoon space drukken hé!");
	msgBox->AddMsg("Gewoon space drukken hé!");
	msgBox->AddMsg("Gewoon space drukken hé! LOOOOL");
	msgBox->setX(300);
	msgBox->setY(200);
	msgBox->setDragable(true);

	//msgBox->SetKeyHandler(Functors::TestMessageBoxKeyHandler());
	AddWindow(msgBox, 1);
}

void NLS::UI::AddWindow(NLS::UI::Window *window, int32_t layer) {
	windows[layer].push_back(window);
}

void NLS::UI::RemoveWindow(NLS::UI::Window *window) {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < windows[i].size(); i++) {
			if (windows[i][j] == window) {

			}
		}
	}
}

void NLS::UI::Draw() {
	for (int32_t layerI = 4; layerI > 0; layerI--) {
		for (size_t i = 0; i < windows[layerI].size(); i++) {
			if (windows[layerI][i]->isVisible())
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
		if (chatlog.size() < maxLinesShown) {
			curPos += textLineHeight * (maxLinesShown - chatlog.size());
		}
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
	}
	

	for (int32_t layerI = 4; layerI > 0; layerI--) {
		for (size_t i = 0; i < windows[layerI].size(); i++) {
			auto window = windows[layerI][i];
			auto children = window->getChildren();
			if (window->handleKey(key)) return true;
			for (size_t j = 0; j < children.size(); j++) {
				if (children[j] != nullptr) {
					if (children[j]->handleKey(key)) return true;
				}
			}
		}
	}
	return false;
}

void NLS::UI::HandleChar(uint32_t ch) {
	if (enteringtext) {
		switch (ch) {
		case 0x16: return; // CTRL + V charcode... not needed!
		case 0x8:
			if (chat.size() > 0) {
				chat.erase(chat.size()-1);
			}
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
		return;
	}

	for (int32_t layerI = 0; layerI < 4; layerI++) {
		for (size_t i = 0; i < windows[layerI].size(); i++) {
			auto window = windows[layerI][i];
			auto children = window->getChildren();
			if (window->handleChar(ch)) return;
			for (size_t j = 0; j < children.size(); j++) {
				if (children[j] != nullptr) {
					if (children[j]->handleChar(ch)) return;
				}
			}
		}
	}
}
bool NLS::UI::HandleMousePress(sf::Mouse::Button btn, int x, int y) {
	for (int32_t layerI = 4; layerI > 0; layerI--) {
		for (vector<NLS::UI::Window *>::iterator iter = windows[layerI].begin(); iter != windows[layerI].end(); iter++) {
			auto wnd = *iter;
			if (!wnd->isDragable()) continue;
			int vx = wnd->getViewX();
			int vy = wnd->getViewY();
			if (vx <= x && vx + wnd->getWidth() >= x) {
				if (vy <= y && vy + wnd->getHeight() >= y) {
					//wnd->setX(x);
					//wnd->setY(y);
					wnd->setDragX(x - vx);
					wnd->setDragY(y - vy);
					wnd->setDragging(true);
					return true;
				}
			}
		}
	}
	return false;
}
bool NLS::UI::HandleMouseRelease(sf::Mouse::Button, int, int) {
	bool k = false;
	for (int32_t layerI = 4; layerI > 0; layerI--) {
		for (vector<NLS::UI::Window *>::iterator iter = windows[layerI].begin(); iter != windows[layerI].end(); iter++) {
			auto wnd = *iter;
			if (wnd->isGrabbed()) {
				wnd->setDragging(false);
				k = true;
			}
		}
	}
	return k;
}
void NLS::UI::HandleMouseMove(int x, int y) {
	for (int32_t layerI = 4; layerI > 0; layerI--) {
		for (size_t i = 0; i < windows[layerI].size(); i++) {
			auto wnd = windows[layerI][i];
			if (wnd->isGrabbed()) {
				wnd->setX(x - wnd->getDragX());
				wnd->setY(y - wnd->getDragY());
			}
		}
	}
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

string NLS::UI::GetClipboardText() {
#ifdef NLS_WINDOWS
	HANDLE clip;
	if (OpenClipboard(NULL)) {
		clip = GetClipboardData(CF_TEXT);
		return string((char *)clip);
	}
#else
#endif
	return "";
}

void NLS::UI::Dialog::Draw() {
	int lines = msg.size();

	if (getHeight() == 0) {
		int height = bottom.data->height + top.data->height + (middle.data->height * lines);
		setHeight(height);
		setWidth(bottom.data->width);
	}

	top.Draw(getViewX(), getViewY());
	for (int i = 0; i < lines; i++) {
		middle.Draw(getViewX(), getViewY() + top.data->height + (middle.data->height * i));
	}
	bottom.Draw(getViewX(), getViewY() + top.data->height + (middle.data->height * lines));
	for (int i = 0; i < msg.size(); i++) {
		NLS::Text txt(msg[i], 14);
		txt.Draw(getViewX() + middle.data->width/2 - (txt.getTextWidth() / 2), getViewY() + top.data->height + (20 * i));
	}
}

void NLS::UI::Dialog::SetImages(int8_t type) {
	NLS::Node base = WZ["UI"]["Basic"]["YesNo" + string(type == 1 ? "2" : "3")];
	SetImages(base["t"], base["c"], base["s"]);
}

void NLS::UI::AddChatlog(const string& msg, NLS::Text::TextColor color) {
	chatlog.push_back(NLS::Text(msg, 14, color));
	if (chatlog.size() >= 50) {
		// Remove first message from list
		chatlog.erase(chatlog.begin());
	}
	
	chatlogCurrentTopmostLine = chatlog.size() < maxLinesShown ? 0 : chatlog.size() - maxLinesShown;
}
*/
