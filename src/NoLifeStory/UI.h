////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
//TODO - Move this stuff into separate files, perhaps a separate folder entirely?
namespace NLS {
	namespace UI {
		extern bool Focused;//All input goes straight to UI
		class Element {
		public:
			Element(Element* parent);
			Element();
			void Draw();
			void HandleKey(sf::Keyboard::Key);
			int CalcX() {return x+(parent?parent->CalcX():0);}
			int CalcY() {return y+(parent?parent->CalcY():0);}
			Element *parent;
			int x, y;
			int width, height;
			vector<Element*> children;
		private:
			Element(const Element&);
		} extern Screen;
		class Movable : public Element {
		public:
			int GrabX;
			int GrabY;
			static Movable* Grabbed;
		};
		class Window : public Element {
		public:
		};
		class Button : public Element {
		public:
		};
		class TextBox : public Element {
		public:
			static TextBox* Active;
			void Send();
			void HandleChar(char32_t);
			u32string text;
		};
		class ScrollBar : public Element {
		public:
			int LineHeight;
			int CurLine;
		};
		void Init();
		bool HandleKey(sf::Event);
		void HandleChar(uint32_t);
		bool HandleMousePress(sf::Mouse::Button, int, int);
		bool HandleMouseRelease(sf::Mouse::Button, int, int);
		bool HandleMouseScroll(int, int, int);
		string GetClipboardText();
	}
}
