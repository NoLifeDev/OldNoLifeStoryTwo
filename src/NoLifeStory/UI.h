////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace UI {
		class Element {
		public:
			Element(Element *parent) : parent(parent), dragable(false), visible(true), 
				enabled(true), dragging(false), width(0), height(0) { }
			Element() : parent(nullptr), dragable(false), visible(true), 
				enabled(true), dragging(false), width(0), height(0) { }

			void setX(int32_t v) { x = v; }
			void setY(int32_t v) { y = v; }
			void setDragX(int32_t v) { dragx = v; }
			void setDragY(int32_t v) { dragy = v; }
			void setWidth(int32_t v) { width = v; }
			void setHeight(int32_t v) { height = v; }
			void setDragable(bool v) { dragable = v; }
			void setVisible(bool v) { visible = v; }
			void setEnabled(bool v) { enabled = v; }
			void setDragging(bool v) { dragging = v; }
			void setParent(Element *v) { parent = v; }
			void addChild(Element *v) { children.push_back(v); v->setParent(this); }
			virtual void Draw() = 0;
			bool isGrabbed() const { return dragging; }

			Element * getParent() { return parent; }
			bool isDragable() const { return dragable; }
			bool isVisible() const { return visible; }
			bool isEnabled() const { return enabled; }
			int32_t getX() { return x; }
			int32_t getY() { return y; }
			int32_t getDragX() { return dragx; }
			int32_t getDragY() { return dragy; }
			int32_t getViewX() { return x + (parent != nullptr ? parent->getViewX() : 0); }
			int32_t getViewY() { return y + (parent != nullptr ? parent->getViewY() : 0); }
			int32_t getWidth() { return width; }
			int32_t getHeight() { return height; }
			virtual bool handleKey(sf::Keyboard::Key key) { return false; }
			virtual bool handleChar(uint32_t ch) { return false; }
			vector<Element *> getChildren() const { return children; }
		protected:
			vector<Element *> children;
		private:
			Element *parent;
			int32_t x, y, dragx, dragy;
			int32_t width, height;
			bool dragable, visible, enabled, dragging;
		};
		class Window : public Element {
		public:
			virtual void Draw();
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
		class Dialog : public Window {
		public:
			void Draw();
			void AddMsg(const string &v) { msg.push_back(v); }
			void SetImages(int8_t type);
			void SetImages(NLS::Sprite t, NLS::Sprite m, NLS::Sprite b) { top = t; middle = m; bottom = b; }
		private:
			vector<string> msg;
			NLS::Sprite top, middle, bottom;
		};

		class DialogWelcome : public Dialog {
		public:
			virtual bool handleKey(sf::Keyboard::Key k) {
				if (Element::handleKey(k)) return true;
				if (k == sf::Keyboard::Space) {
					
				}
			}
		};


		void Init();
		void AddWindow(NLS::UI::Window *, int32_t);
		void RemoveWindow(NLS::UI::Window *);
		void Draw();
		bool HandleKey(sf::Event);
		void HandleChar(uint32_t);
		bool HandleMousePress(sf::Mouse::Button, int, int);
		bool HandleMouseRelease(sf::Mouse::Button, int, int);
		void HandleMouseMove(int, int);
		bool HandleMouseScroll(int, int, int);
		string GetClipboardText();
		void AddChatlog(const string&, NLS::Text::TextColor = NLS::Text::TextColor());
	}
}
