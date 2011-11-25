////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Text {
	public:
		struct TextColor {
			TextColor() : Red(0), Green(0), Blue(0), Alpha(1) { }
			TextColor(float r, float g, float b, float a = 1.0f) : Red(r), Green(g), Blue(b), Alpha(a) { }
			TextColor(int32_t r, int32_t g, int32_t b, int32_t a = 255) // ...
			{
				float factor = 1.0f / 255;
				Red = (uint8_t)r * factor;
				Green = (uint8_t)g * factor;
				Blue = (uint8_t)b * factor;
				Alpha = (uint8_t)a * factor;
			}
			TextColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
			{
				float factor = 1.0f / 255;
				Red = r * factor;
				Green = g * factor;
				Blue = b * factor;
				Alpha = a * factor;
			}

			float Red;
			float Green;
			float Blue;
			float Alpha;
		};

		static void Init();
		static void Unload();
		Text(const string &str, int size, TextColor clr = TextColor(0, 0, 0, 255));
		void Draw(int x, int y);
		int32_t getTextWidth();
		int32_t getTextHeight();
	private:
		basic_string<uint32_t> text;
		int fsize;
		TextColor color;
	};
}