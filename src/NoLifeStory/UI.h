////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace UI {
		void Init();
		void Draw();
		bool HandleKey(sf::Keyboard::Key);
		void HandleChar(uint32_t);
		bool HandleMousePress(sf::Mouse::Button, int, int);
		bool HandleMouseRelease(sf::Mouse::Button, int, int);
		bool HandleMouseScroll(int, int, int);
		class Element {

		};
		class Window : public Element {

		};
		class Button : public Element {

		};
		class TextField : public Element {

		};
		class ScrollBar : public Element {

		};
	}
}
