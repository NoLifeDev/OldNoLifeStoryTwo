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
			virtual void HandleClick(sf::Event::MouseButtonEvent) {}
			void Focus();
			virtual void HandleKey(sf::Keyboard::Key) {}
			void Add(Element* e);
			vector<Element*> Elements;
			int x, y;
			int width, height;
			bool focusable, stealsfocus;
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
			virtual void Click(sf::Mouse::Button) {};
			int CalcX() {return x+parent->x;}
			int CalcY() {return y+parent->y;}
			int x, y;
			int width, height;
			Window* parent;
			vector<Element*> children;
		private:
			Element(const Element&);
		};
		class Movable : public Element {
		public:
		};
		class Button : public Element {
		public:
			function<void()> action;
		};
		class TextBox : public Element {
		public:
			TextBox(int x, int y, int width)
			: Element(x, y, width, 20) {}
			static TextBox* Active;
			void Send();
			void Draw();
			void HandleChar(char32_t);
			u32string str;
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
		void Init();
		void Draw();
		extern bool Focused;
	}
}
