////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Text {
	public:
		static void Init();
		static void Unload();
		static u32string Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		Text();
		void Set(u32string str, int size);
		void Draw(int x, int y);
		int Width();
		int Height();
	private:
		u32string text;
		int fsize;
		int width, height;
		sf::RenderTexture* tex;
	};
}