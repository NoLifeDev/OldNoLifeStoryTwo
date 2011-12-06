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
	if (WZ["UI"]["StatusBar2"]) {
		Style = Modern;
	} else {
		Style = Clean;
	}
	new StatusBar();
	//new LoginDialog();
	//new BaseGUI();
}
void NLS::UI::Draw() {
	for_each(Window::begin(), Window::end(), [](Window* w){
		w->Draw();
	});
}

NLS::UI::Window::Window(int x, int y, int width, int height, bool focusable, bool stealsfocus, bool visible)
	: x(x), y(y), width(width), height(height), focusable(focusable), stealsfocus(stealsfocus), visible(visible) {
	All.push_back(this);
}
NLS::UI::Window::~Window() {
	All.erase(find(begin(), end(), this));
}
void NLS::UI::Window::Add(Element* e) {
	Elements.push_back(e);
	e->parent = this;
}
void NLS::UI::Window::Draw() {
	if (!visible) return;
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
bool NLS::UI::Window::HandleKey(sf::Keyboard::Key key) {
	if (actions[key]) actions[key]();
	else return false;
	return true;
}

bool NLS::UI::Element::CheckPosition(INT mouseX,INT mouseY,bool bPressed) {
	bool bFound = FALSE;
	if (mouseX >= CalcX() && mouseX <= CalcX() - width) {
		if (mouseY >= CalcY() && mouseY <= CalcY() + height) {
			bFound = TRUE;
		}
	}
	return bFound;
}
NLS::UI::LoginDialog::LoginDialog() : Window(400-22, 300, 0, 0, false, false), tUsername(-100, -51, 0), tPassword(-100, -26, 0), cbRemember(-100,4), bRemember(-90,0), bLoginLost(-14,0), bPassLost(55,2), bNew(-100,20), bHomePage(-27,20), bQuit(45,20), bLogin(65,-51) {
	tUsername.setBackground(WZ["UI"]["Login"]["Title"]["ID"]);
	tPassword.setBackground(WZ["UI"]["Login"]["Title"]["PW"]);
	cbRemember.setNode(WZ["UI"]["Login"]["Title"]["check"]);
	bRemember.setNode(WZ["UI"]["Login"]["Title"]["BtLoginIDSave"]);
	bLoginLost.setNode(WZ["UI"]["Login"]["Title"]["BtLoginIDLost"]);
	bPassLost.setNode(WZ["UI"]["Login"]["Title"]["BtPasswdLost"]);
	bNew.setNode(WZ["UI"]["Login"]["Title"]["BtNew"]);
	bHomePage.setNode(WZ["UI"]["Login"]["Title"]["BtHomePage"]);
	bQuit.setNode(WZ["UI"]["Login"]["Title"]["BtQuit"]);
	bLogin.setNode(WZ["UI"]["Login"]["Title"]["BtLogin"]);
	
	bRemember.action = [this]() {
		cbRemember.bChecked = !cbRemember.bChecked;
	};
	bLoginLost.action = [this]() {
		ShellExecute(NULL, "open", "http://maplestory.nexon.net" ,NULL, NULL, SW_SHOWNORMAL);
	};
	bPassLost.action = [this]() {
		ShellExecute(NULL, "open", "http://maplestory.nexon.net" ,NULL, NULL, SW_SHOWNORMAL);
	};

	bNew.action = [this]() {
		ShellExecute(NULL, "open", "http://maplestory.nexon.net" ,NULL, NULL, SW_SHOWNORMAL);
	};
	bHomePage.action = [this]() {
		ShellExecute(NULL, "open", "http://maplestory.nexon.net" ,NULL, NULL, SW_SHOWNORMAL);
	};
	bQuit.action = [this]() {
		NLS::Unload();
	};

	bLogin.action = [this]() {
		if(tUsername.str.length() < 4 || tPassword.str.length() < 4)
			return;
		MessageBoxA(0,(char*)tUsername.str.c_str(),(char*)tPassword.str.c_str(),0);
	};

	Add(&tUsername);
	Add(&tPassword);
	Add(&cbRemember);
	Add(&bRemember);
	Add(&bLoginLost);
	Add(&bPassLost);
	Add(&bNew);
	Add(&bHomePage);
	Add(&bQuit);
	Add(&bLogin);

	setBackground(WZ["UI"]["Login"]["Title"]["signboard"]);
}
void NLS::UI::LoginDialog::Draw() {
	if(NLS::Map::curmap == "MapLogin")
		Window::Draw();
}
NLS::UI::BaseGUI::BaseGUI() : Window(512, 515+84, 0, 0, false, false) , tChat(25,0,0), sLevelBG(0,0), sLevelCover(0,0), sGaugeBG(0,0), sGaugeCover(0,0), sNotice(0,0), sChatCover(0,0), sChatSpace(0,0), bCashshop(0,0), bChattarget(0,0), bCharacter(0,0), bChat(0,0), bClaim(0,0), bEquip(0,0), bInvent(0,0), bKeySettings(0,0), bMenu(0,0), bMTS(0,0), bQuest(0,0), bSkill(0,0), bStat(0,0), bSystem(0,0), bChatclose(0,0) {
	tChat.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["chatEnter"]);

	sLevelBG.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["lvBacktrnd"]);
	sLevelCover.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["lvCover"]);
	sGaugeBG.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["gaugeBackgrd"]);
	sGaugeCover.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["gaugeCover"]);
	sNotice.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["notice"]);
	sChatCover.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["chatCover"]);
	sChatSpace.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["chatSpace2"]);

	bCashshop.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtCashShop"]);
	bChattarget.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["chatTarget"]["base"]);
	bCharacter.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtCharacter"]);
	bChat.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtChat"]);
	bClaim.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtClaim"]);
	bEquip.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtEquip"]);
	bInvent.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtInven"]);
	bKeySettings.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtKeysetting"]);
	bMenu.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtMenu"]);
	bMTS.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtMTS"]);
	bQuest.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtQuest"]);
	bSkill.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtSkill"]);
	bStat.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtStat"]);
	bSystem.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["BtSystem"]);
	bChatclose.setNode(WZ["UI"]["StatusBar2"]["mainBar"]["chatClose"]);

	Add(&sLevelBG);
	Add(&sLevelCover);
	Add(&sGaugeBG);
	Add(&sGaugeCover);
	Add(&sNotice);
	Add(&sChatCover);
	Add(&sChatSpace);

	Add(&bCashshop);
	Add(&bChattarget);
	Add(&bCharacter);
	Add(&bChat);
	Add(&bClaim);
	Add(&bEquip);
	Add(&bInvent);
	Add(&bKeySettings);
	Add(&bMenu);
	Add(&bMTS);
	Add(&bQuest);
	Add(&bSkill);
	Add(&bStat);
	Add(&bSystem);
	Add(&bChatclose);

	Add(&tChat);
	
	setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["backgrnd"]);
}
void NLS::UI::BaseGUI::Draw() {
	if(NLS::Map::curmap != "MapLogin") {
		Window::Draw();

		Text t;
		t.Set(Text::Color(255, 255, 255)+u32("Warrior"),12);
		t.Draw(76, 566);

		t.Set(Text::Color(255, 255, 255)+u32(NLS::ThisPlayer->name),12);
		t.Draw(76, 582);
	}
}

NLS::UI::StatusBar::StatusBar() : Window(0, 500, 800, 100, false, false), text(20, 20, 400) {
	Add(&text);
	Key::Set(sf::Keyboard::Return, [this](){TextBox::Active = &this->text;});
	Key::Set(sf::Keyboard::H, [](){Map::Load("100000000", "");});
}
void NLS::UI::StatusBar::Draw() {

	glPushMatrix();
	glTranslatef(x, y, 0);
	glColor4f(0.5, 0.5, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(width, 0);
	glVertex2i(width, height);
	glVertex2i(0, height);
	glEnd();
	glPopMatrix();

	Window::Draw();
}
void NLS::UI::Static::Draw() {
	background.Draw(CalcX(),CalcY());
}
void NLS::UI::Button::setNode(NLS::Node nNode) {
	this->nNode = nNode;
	setState(BTN_NORMAL);
}
void NLS::UI::Button::Draw() {
	background.Draw(CalcX(),CalcY());
}
bool NLS::UI::Button::CheckPosition(INT mouseX,INT mouseY,bool bPressed) {
	bool bFound = FALSE;
	if (mouseX >= CalcX()-background.data->originx && mouseX <= CalcX() - background.data->originx + width) {
		if (mouseY >= CalcY()-background.data->originy && mouseY <= CalcY() - background.data->originy + height) {
			bFound = TRUE;
		}
	}
	if(bFound) {
		setState(bPressed ? BTN_PRESSED : BTN_MOUSE_OVER);
	} else
		setState(BTN_NORMAL);
	return bFound;
}

void NLS::UI::Button::Click(sf::Mouse::Button b) {
	if(b == sf::Mouse::Left) {
		if(action)
			action();
	}
}

void NLS::UI::Button::setState(EBState iState) {
	if(this->iState == iState)
		return;
	std::string szState;
	switch(iState) {
		case BTN_NORMAL:
			szState = "normal";
			break;
		case BTN_MOUSE_OVER:
			szState = "mouseOver";
			break;
		case BTN_PRESSED:
			szState = "pressed";
			break;
		case BTN_DISABLED:
			szState = "disabled";
			break;
		default:
			return;
	}
	setBackground(nNode[szState][0]);
	this->iState = iState;
}
void NLS::UI::CheckBox::setNode(NLS::Node nNode) {
	this->nNode = nNode;
}
void NLS::UI::CheckBox::Draw() {
	NLS::Sprite s = nNode[bChecked ? "1" : "0"];
	s.Draw(CalcX(),CalcY());
}
bool NLS::UI::CheckBox::CheckPosition(INT mouseX,INT mouseY,bool bPressed) {
	NLS::Sprite s = nNode[bChecked ? "1" : "0"];

	width = s.data->width;
	height = s.data->height;

	bool bFound = FALSE;
	if (mouseX >= CalcX()-s.data->originx && mouseX <= CalcX() - s.data->originx + width) {
		if (mouseY >= CalcY()-s.data->originy && mouseY <= CalcY() - s.data->originy + height) {
			bFound = TRUE;
		}
	}
	return bFound;
}
void NLS::UI::CheckBox::Click(sf::Mouse::Button b) {
	if(b == sf::Mouse::Left) {
		bChecked = !bChecked;
	}
}
bool NLS::UI::TextBox::CheckPosition(INT mouseX,INT mouseY,bool bPressed) {
	return Mouse::x > CalcX() and Mouse::x <= CalcX()+width and Mouse::y >= CalcY() and Mouse::y <= CalcY()+height;
}

void NLS::UI::TextBox::Click(sf::Mouse::Button b) {
	TextBox::Active = this;
	/*INT iIndex = 0;
	iIndex = (sf::Mouse::GetPosition().x - this->x+2) / 7;
	if(iIndex > str.length())
		iIndex = str.length();
	szIndex = iIndex;*/
}
void NLS::UI::TextBox::Send() {
	Map::Load(u8(str), "");
	str.clear();
	updateText();
}
void NLS::UI::TextBox::updateText() {
	text.Set(str, 12);
}
void NLS::UI::TextBox::HandleChar(char32_t key) {
	switch (key) {
	case '\r':
	case '\n':
	case '\t':
		return;
	case '\b':
		if (!str.empty()) str.erase(str.end());
		return;
	}
	str += key;
	updateText();
}

void NLS::UI::TextBox::HandleKey(sf::Keyboard::Key key) {
	if(key == sf::Keyboard::Back && szIndex > 0) {
		str.erase(szIndex-1,1);
		szIndex--;
		updateText();
	}
	if(key == sf::Keyboard::Delete && szIndex < str.length()) {
		str.erase(szIndex,1);
		updateText();
	}
	if(key == sf::Keyboard::Right && szIndex < str.length()) {
		szIndex++;
	}
	if(key == sf::Keyboard::Left && szIndex > 0) {
		szIndex--;
	}

}
void NLS::UI::TextBox::Draw() {
	glPushMatrix();
	glTranslatef(CalcX(), CalcY(), 0);
	if (Active != this) glColor4f((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, 1);
	else glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(width, 0);
	glVertex2i(width, height);
	glVertex2i(0, height);
	glEnd();
	text.Draw(3, 3);
	glPopMatrix();
	/*
	if (Active) {
		Key::Left = false;
		Key::Right = false;
		Key::Up = false;
		Key::Down = false;
	}
	UINT _x = CalcX() + 3;
	UINT _y = CalcY() + 5;
	if(str.length() == 0)
		background.Draw(x,y);

	text.Draw(_x, _y);

	if(Active == this) {
		if(GetTickCount() % 1000 < 500) {
			glColor4f(0, 0, 0, 1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBegin(GL_QUADS);

			UINT nCarret = str.length() == 0 ? 0 : text.Width() / str.length();
			_x = _x - 1 + (szIndex * nCarret);
			_y = CalcY()  + 2;

			int32_t h = background.data->height-4;
			glVertex2i(_x, _y);
			glVertex2i(_x + 1, _y);
			glVertex2i(_x + 1, _y + h);
			glVertex2i(_x, _y + h);
			glEnd();
		}
	}
	*/
}
void NLS::UI::Element::setBackground(NLS::Sprite bg) {
	width = bg.data->width;
	height = bg.data->height;
	background = bg;
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
