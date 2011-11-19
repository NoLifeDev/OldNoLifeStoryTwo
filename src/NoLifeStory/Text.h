////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Text {
	public:
		static void Init();
		static void Unload();
		Text(string str, int size);
		void Draw(int x, int y);
	private:
		basic_string<uint32_t> text;
		int fsize;
	};
}