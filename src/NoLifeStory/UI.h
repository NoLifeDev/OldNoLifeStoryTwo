////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace UI {
		class Element {
		public:
			Element(Element *parent) : parent(parent), dragable(false), visible(true), enabled(true) { }
			Element() : parent(nullptr), dragable(false), visible(true), enabled(true) { }

			void setX(int32_t v) { x = v; }
			void setY(int32_t v) { y = v; }
			void setWidth(int32_t v) { width = v; }
			void setHeight(int32_t v) { height = v; }
			void setDragable(bool v) { dragable = v; }
			void setVisible(bool v) { visible = v; }
			void setEnabled(bool v) { enabled = v; }
			void setParent(Element *v) { parent = v; }
			void addChild(Element *v) { children.push_back(v); v->setParent(this); }
			virtual void Draw() = 0;
			bool Grabbed() { return visible && enabled && dragable; }

			Element * getParent() { return parent; }
			bool isDragable() const { return dragable; }
			bool isVisible() const { return visible; }
			bool isEnabled() const { return enabled; }
			int32_t getX() { return x; }
			int32_t getY() { return y; }
			int32_t getViewX() { return x + (parent != nullptr ? parent->getViewX() : 0); }
			int32_t getViewY() { return y + (parent != nullptr ? parent->getViewY() : 0); }
			int32_t getWidth() { return width; }
			int32_t getHeight() { return height; }
		protected:
			vector<Element *> children;
		private:
			Element *parent;
			int32_t x, y;
			int32_t width, height;
			bool dragable, visible, enabled;
		};
		class Window : public Element {
		public:
			void Draw();
			bool Grabbed();

			void setTitleBarHeight(int32_t v) { titleBarHeight = v; }
			void setBackground(NLS::Sprite bg);
		private:
			int32_t titleBarHeight;
			NLS::Sprite background;
		};
		class Button : public Element {
		public:
			void Draw();

		};
		class TextField : public Element {
		public:
			void Draw();

		};
		class ScrollBar : public Element {
		public:
			void Draw();

		};
		class Image : public Element {
		public:
			void Draw();
			void setSprite(NLS::Sprite v) { sprite = v; }
		private:
			NLS::Sprite sprite;
		};
		class AnimatedImage : public Element {
		public:
			void Draw();

			void setSprite(NLS::AniSprite v) { sprite = v; }
		private:
			NLS::AniSprite sprite;
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
		void AddChatlog(const string&, NLS::Text::TextColor = NLS::Text::TextColor());
	}
}
