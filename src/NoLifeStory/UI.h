////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace UI {
		class Element;
		class Window {
		public:
			Window(int x, int y, int width, int height, bool focusable, bool stealsfocus);
			virtual ~Window();
			virtual void Draw();
			void setBackground(NLS::Sprite bg);
			virtual void HandleClick(UINT x,UINT y,sf::Mouse::Button b);
			virtual bool CheckPosition(INT mouseX,INT mouseY,bool bPressed);
			void Focus();
			bool HandleKey(sf::Keyboard::Key);
			void Add(Element* e);
			vector<Element*> Elements;
			map<sf::Keyboard::Key, function<void()>> actions;
			int x, y;
			int width, height;
			bool focusable, stealsfocus,bVisible;
			NLS::Sprite background;
			static list<Window*> All;
			static list<Window*>::iterator begin() {return All.begin();}
			static list<Window*>::iterator end() {return All.end();}
		private:
			Window(const Window&);
		};
		class Element {
		public:
			Element(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			virtual ~Element() {}
			virtual void Draw() {};
			void setBackground(NLS::Sprite bg);
			virtual bool CheckPosition(INT mouseX,INT mouseY,bool bPressed);
			virtual void Click(sf::Mouse::Button) {};
			int CalcX() {return x+parent->x;}
			int CalcY() {return y+parent->y;}
			int x, y;
			int width, height;
			Window* parent;
			NLS::Sprite background;
			vector<Element*> children;
		private:
			Element(const Element&);
		};
		class Movable : public Element {
		public:
		};
		class Static: public Element {
		public:
			Static(int x,int y) : Element(x,y,0,0) {}
			void Draw();
		};
		class Button : public Element {
		public:
			enum EBState {
				BTN_NORMAL,
				BTN_MOUSE_OVER,
				BTN_PRESSED,
				BTN_DISABLED,
				BTN_INVISIBLE
			};
			Button(int x, int y)
				: Element(x, y, 0, 0) {
					iState = BTN_INVISIBLE;
					action = NULL;
			}
			void Click(sf::Mouse::Button);
			void Draw();
			bool CheckPosition(INT mouseX,INT mouseY,bool bPressed);
			void setNode(NLS::Node nNode);
			void setState(EBState iState);
			function<void()> action;
			NLS::Node nNode;
			EBState iState;
		};
		class CheckBox : public Element {
		public:
			CheckBox(int x,int y) : Element(x,y,0,0) {}
			void Draw();
			bool CheckPosition(INT mouseX,INT mouseY,bool bPressed);
			void Click(sf::Mouse::Button);
			void setNode(NLS::Node nNode);
			NLS::Node nNode;
			bool bChecked;
		};
		class TextBox : public Element {
		public:
			TextBox(int x, int y, int width)
				: szIndex(0), Element(x, y, width, 20) {}
			static TextBox* Active;
			void Send();
			void Draw();
			bool CheckPosition(INT mouseX,INT mouseY,bool bPressed);
			void Click(sf::Mouse::Button);
			void HandleChar(char32_t);
			void HandleKey(sf::Keyboard::Key);
			void updateText();
			u32string str;
			int szIndex;
			Text text;
		};
		class ScrollBar : public Element {
		public:
			int LineHeight;
			int CurLine;
		};
		class StatusBar : public Window {
		public:
			StatusBar();
			void Draw();
			TextBox text;
		};
		class LoginDialog : public Window {
		public:
			LoginDialog();
			void Draw();
			TextBox tUsername;
			TextBox tPassword;
			CheckBox cbRemember;
			Button bRemember;
			Button bLoginLost;
			Button bPassLost;
			Button bNew;
			Button bHomePage;
			Button bQuit;
			Button bLogin;
		};
		class BaseGUI : public Window {
		public:
			BaseGUI();
			void Draw();
			TextBox tChat;

			Static sLevelBG;
			Static sLevelCover;
			Static sGaugeBG;
			Static sGaugeCover;
			Static sNotice;
			Static sChatCover;
			Static sChatSpace;

			Button bCashshop;
			Button bChattarget;
			Button bCharacter;
			Button bChat;
			Button bClaim;
			Button bEquip;
			Button bInvent;
			Button bKeySettings;
			Button bMenu;
			Button bMTS;
			Button bQuest;
			Button bSkill;
			Button bStat;
			Button bSystem;
			Button bChatclose;
		};
		void Init();
		void Draw();
		extern bool Focused;
	}
}
