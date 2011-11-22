////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace UI {
		extern bool Focused;//All input goes straight to UI
		extern bool Typing;//All input goes straight to textbox
		class Element {
		public:
			Element(Element* parent);
			Element();
			void Draw();
			int32_t CalcX() {return x+(parent?parent->CalcX():0);}
			int32_t CalcY() {return y+(parent?parent->CalcY():0);}
			Element *parent;
			int x, y;
			int width, height;
			vector<Element*> children;
		} extern Screen;
		class Window : public Element {
		public:
		};
		class Button : public Element {
		public:
		};
		class TextBox : public Element {
		public:
		};
		class ScrollBar : public Element {
		};
		void Init();
		void AddWindow(NLS::UI::Window *, int32_t);
		void Draw();
		bool HandleKey(sf::Event);
		void HandleChar(uint32_t);
		bool HandleMousePress(sf::Mouse::Button, int, int);
		bool HandleMouseRelease(sf::Mouse::Button, int, int);
		bool HandleMouseScroll(int, int, int);
		string GetClipboardText();
	}
}
