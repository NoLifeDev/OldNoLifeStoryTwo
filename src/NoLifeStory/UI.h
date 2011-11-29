////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace UI {
		class Element;
		class Window {
		public:
			Window();
			virtual void Draw();
			virtual void HandleClick(sf::Event::MouseButtonEvent);
			void Focus();
			virtual void HandleKey(sf::Keyboard::Key)=0;
			vector<Element*> Elements;
			int x, y;
			int width, height;
			bool focusable, stealsfocus;
			static list<Window*> All;
			static list<Window*>::iterator begin() {return All.begin();}
			static list<Window*>::iterator end() {return All.end();}
		};
		class Element {
		public:
			Element(Window* parent) : parent(parent) {}
			virtual void Draw();
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
			static TextBox* Active;
			void Send() {}
			void HandleChar(char32_t) {}
			u32string text;
		};
		class ScrollBar : public Element {
		public:
			int LineHeight;
			int CurLine;
		};
		void Init();
		void Draw();
		extern bool Focused;
	}
}
