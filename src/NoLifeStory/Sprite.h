////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class SpriteData {
	public:
		GLuint texture;
		GLint width, height;
		GLint originx, originy;
		bool loaded;
		void* png;
	};
	class Sprite {
	public:
		Sprite();
		void Draw(int x, int y, bool flipped = false, float alpha = 1, float rotation = 0);
		void GetTexture();
		static void Unload();
		SpriteData* data;
		static deque <SpriteData*> loaded;
	};
};