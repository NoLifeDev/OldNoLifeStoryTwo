////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::UI::TextBox* NLS::UI::TextBox::Active = nullptr;
bool NLS::UI::Focused = false;
NLS::UI::StyleEnum NLS::UI::Style = NLS::UI::Clean;
list<NLS::UI::Window*> NLS::UI::Window::All;

#pragma region UI
void NLS::UI::Init() {
	new StatusBar();
	//new LoginDialog();
	//new BaseGUI();
}
void NLS::UI::Draw() {
	for_each(Window::begin(), Window::end(), [](Window* w){
		if (w->visible and w->login == Map::Login) w->Draw();
	});
}
#pragma endregion

#pragma region Window
NLS::UI::Window::Window(int x, int y, int width, int height, bool focusable, bool stealsfocus, bool visible, bool login)
	: x(x), y(y), width(width), height(height), focusable(focusable), stealsfocus(stealsfocus), visible(visible), login(login) {
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
	if (Style == Clean) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x+width, y);
		glVertex2i(x+width, y+height);
		glVertex2i(x, y+height);
		glEnd();
	}
	for_each(Elements.begin(), Elements.end(), [&](Element* e){
		e->Draw();
	});
}
void NLS::UI::Window::Focus() {
	if (!focusable) return;
	if (All.back() == this) return;
	if (All.back()->stealsfocus) return;
	if (Map::Login != login) return;
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
#pragma endregion

#pragma region Element
void NLS::UI::Element::Draw() {
	if (Style == Clean) {
		int x = CalcX();
		int y = CalcY();
		glBindTexture(GL_TEXTURE_2D, 0);
		glBegin(GL_QUADS);
		glVertex2i(x, y);
		glVertex2i(x+width, y);
		glVertex2i(x+width, y+height);
		glVertex2i(x, y+height);
		glEnd();
	}
}
#pragma endregion

#pragma region LoginDialog
NLS::UI::LoginDialog::LoginDialog() : Window(378, 300, 0, 0, false, false, true, true)/*, tUsername(-100, -51, 0), tPassword(-100, -26, 0), cbRemember(-100,4), bRemember(-90,0), bLoginLost(-14,0), bPassLost(55,2), bNew(-100,20), bHomePage(-27,20), bQuit(45,20), bLogin(65,-51) */{
/*	tUsername.setBackground(WZ["UI"]["Login"]["Title"]["ID"]);
	tPassword.setBackground(WZ["UI"]["Login"]["Title"]["PW"]);
	cbRemember.setNode(WZ["UI"]["Login"]["Title"]["check"]);
	bRemember.setNode(WZ["UI"]["Login"]["Title"]["BtLoginIDSave"]);
	bLoginLost.setNode(WZ["UI"]["Login"]["Title"]["BtLoginIDLost"]);
	bPassLost.setNode(WZ["UI"]["Login"]["Title"]["BtPasswdLost"]);
	bNew.setNode(WZ["UI"]["Login"]["Title"]["BtNew"]);
	bHomePage.setNode(WZ["UI"]["Login"]["Title"]["BtHomePage"]);
	bQuit.setNode(WZ["UI"]["Login"]["Title"]["BtQuit"]);
	bLogin.setNode(WZ["UI"]["Login"]["Title"]["BtLogin"]);*/

	/*
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
	*/
//	setBackground(WZ["UI"]["Login"]["Title"]["signboard"]);
}
void NLS::UI::LoginDialog::Draw() {
	Window::Draw();
}
#pragma endregion

#pragma region StatusBar
NLS::UI::StatusBar::StatusBar() : Window(0, 500, 800, 100, false, false, true, false), text(20, 20, 400) {
	Add(&text);
	Key::Set(sf::Keyboard::Return, [this](){TextBox::Active = &this->text;});
/*
NLS::UI::BaseGUI::BaseGUI() : Window(512, 515+84, 0, 0, false, false,false) , tChat(25,0,0), 
	sLevelBG(0,0,WZ["UI"]["StatusBar2"]["mainBar"]["lvBacktrnd"]), 
	sLevelCover(0,0,WZ["UI"]["StatusBar2"]["mainBar"]["lvCover"]), 
	sGaugeBG(0,0,WZ["UI"]["StatusBar2"]["mainBar"]["gaugeBackgrd"]), 
	sGaugeCover(0,0,WZ["UI"]["StatusBar2"]["mainBar"]["gaugeCover"]), 
	sNotice(0,0,WZ["UI"]["StatusBar2"]["mainBar"]["notice"]), 
	sChatCover(0,0,WZ["UI"]["StatusBar2"]["mainBar"]["chatCover"]), 
	sChatSpace(0,0,WZ["UI"]["StatusBar2"]["mainBar"]["chatSpace2"]), 
	bCashshop(0,0), bChattarget(0,0), bCharacter(0,0), bChat(0,0), bClaim(0,0), bEquip(0,0), bInvent(0,0), bKeySettings(0,0), bMenu(0,0), bMTS(0,0), bQuest(0,0), bSkill(0,0), bStat(0,0), bSystem(0,0), bChatclose(0,0) {
	tChat.setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["chatEnter"]);

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
	
//	setBackground(WZ["UI"]["StatusBar2"]["mainBar"]["backgrnd"]);
}
*/
}
void NLS::UI::StatusBar::Draw() {
	glColor4f(0.2, 0.2, 1, 1);
	Window::Draw();
/*
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
*/
}
#pragma endregion

#pragma region Image
void NLS::UI::Image::Draw() {
	node.operator Sprite().Draw(x, y);
}
#pragma endregion

#pragma region Button
void NLS::UI::Button::Draw() {
	if (this == Mouse::over) {
		if (Mouse::State == Mouse::OnOverClickable) {
			if (pressed) {
				if (action) action();
				pressed = false;
			}
			glColor4f(1, 1, 1, 1);
		} else if (Mouse::State == Mouse::OnOverClickableLocked) {
			glColor4f(0.5, 0.5, 0.5, 1);
		} else {
			glColor4f(1, 0, 0, 1);
		}
	} else {
		if (Mouse::State != Mouse::OnOverClickableLocked) pressed = false;
		if (pressed) glColor4f(0.5, 0.5, 0.5, 1);
		else glColor4f(0.7, 0.7, 0.7, 1);
	}
}
void NLS::UI::Button::Click(sf::Mouse::Button b) {
	if (b == sf::Mouse::Left) pressed = true;
}
#pragma endregion

#pragma region CheckBox
void NLS::UI::CheckBox::Draw() {
	NLS::Sprite s = node[checked ?"1":"0"];
	s.Draw(CalcX(), CalcY());
}
void NLS::UI::CheckBox::Click(sf::Mouse::Button b) {
	if (b == sf::Mouse::Left) checked = !checked;
}
#pragma endregion

#pragma region TextBox
void NLS::UI::TextBox::Click(sf::Mouse::Button b) {
	if (b == sf::Mouse::Left) {
		TextBox::Active = this;
		if (sf::Keyboard::IsKeyPressed(sf::Keyboard::RShift) or sf::Keyboard::IsKeyPressed(sf::Keyboard::LShift)) {
			sel2 = text.GetPos(Mouse::x-CalcX(), false);
		} else {
			sel1 = sel2 = text.GetPos(Mouse::x-CalcX(), false);
		}
		selecting = true;
	}
}
void NLS::UI::TextBox::Send() {
	Map::Load(u8(str), "");
	str.clear();
	UpdateText();
	index = 0;
	size = 0;
	sel1 = 0;
	sel2 = 0;
}
void NLS::UI::TextBox::UpdateText() {
	text.Set(str, 12);
}
void NLS::UI::TextBox::HandleChar(char32_t key) {
	switch (key) {
	case 3:
		SetClipboardText(u8(str.substr(index, size)));
		return;
	case 22:
		{
			u32string more = u32(GetClipboardText());
			str.replace(index, size, more);
			sel1 = sel2 = index+more.size();
			UpdateSelection();
			UpdateText();
			return;
		}
	case 24:
		SetClipboardText(u8(str.substr(index, size)));
		str.erase(index, size);
		sel1 = sel2 = index;
		UpdateSelection();
		UpdateText();
		return;
	case '\r':
	case '\n':
	case '\t':
		return;
	case '\b':
		if (size) {
			str.erase(index, size);
			sel1 = sel2 = index;
		} else if (index) {
			str.erase(index-1, 1);
			sel1 = sel2 = index-1;
		}
		UpdateSelection();
		UpdateText();
		return;
	}
	cout << key << endl;
	str.replace(index, size, 1, key);
	sel1 = sel2 = index+1;
	UpdateSelection();
	UpdateText();
}
void NLS::UI::TextBox::HandleKey(sf::Event::KeyEvent key) {
	switch (key.Code) {
	case sf::Keyboard::Left:
		if (key.Shift) sel2 = max(0, sel2-1);
		else sel1 = sel2 = max(0, sel1-1);
		UpdateSelection();
		break;
	case sf::Keyboard::Right:
		if (key.Shift) sel2 = min(str.size(), sel2+1);
		else sel1 = sel2 = min(str.size(), sel1+1);
		UpdateSelection();
		break;
	case sf::Keyboard::Home:
		sel2 = 0;
		if (!key.Shift) sel1 = sel2;
		UpdateSelection();
		break;
	case sf::Keyboard::End:
		sel2 = str.size();
		if (!key.Shift) sel1 = sel2;
		UpdateSelection();
		break;
	case sf::Keyboard::Delete:
		if (size) {
			str.erase(index, size);
			sel1 = sel2 = index;
		} else if (index < str.size()) {
			str.erase(index, 1);
			sel1 = sel2 = index;
		}
		UpdateSelection();
		UpdateText();
		break;
	}
}
void NLS::UI::TextBox::UpdateSelection() {
	if (sel1 < sel2) {
		index = sel1;
		size = sel2-sel1;
	} else if (sel1 > sel2) {
		index = sel2;
		size = sel1-sel2;
	} else {
		index = sel1;
		size = 0;
	}
}
void NLS::UI::TextBox::Draw() {
	if (selecting) {
		if (Mouse::State == Mouse::OnOverClickableLocked) {
			sel2 = text.GetPos(Mouse::x-CalcX(), false);
			UpdateSelection();
		} else {
			selecting = false;
		}
	}
	if (this == Active) glColor4f(1, 1, 1, 1);
	else glColor4f(0.7, 0.7, 0.7, 1);
	Element::Draw();
	text.Draw(CalcX(), CalcY());
	if (this == Active) {
		if (size) {
			int w1 = text.Width(index);
			int w2 = text.Width(index+size);
			glColor4f(0, 0, 0, 0.5);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBegin(GL_QUADS);
			glVertex2i(CalcX()+w1, CalcY());
			glVertex2i(CalcX()+w1, CalcY()+height);
			glVertex2i(CalcX()+w2, CalcY()+height);
			glVertex2i(CalcX()+w2, CalcY());
			glEnd();
		} else {
			int w = text.Width(index)+1;
			if (Time::tdelta-floor(Time::tdelta) < 0.5) {
				glColor4f(0, 0, 0, 1);
				glBindTexture(GL_TEXTURE_2D, 0);
				glBegin(GL_LINES);
				glVertex2i(CalcX()+w, CalcY());
				glVertex2i(CalcX()+w, CalcY()+height);
				glEnd();
			}
		}
	}
}
#pragma endregion

#pragma region Old crap
/*namespace Functors {
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
}*/
/*void NLS::UI::Element::setBackground(NLS::Sprite bg) {
	width = bg.data->width;
	height = bg.data->height;
	background = bg;
}*/
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
#pragma endregion