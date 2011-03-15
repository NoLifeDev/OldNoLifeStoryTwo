///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

class SpriteData {
public:
	SpriteData();
	WZLib_PNGProperty* data;
	SDL_Surface* sdltexture;
	GLuint gltexture;
	bool loaded;
};
class Sprite {
public:
	Sprite();
	SpriteData* data;
	int width, height;
	double twidth, theight;
	int fwidth, fheight;
	int originx, originy;
	void Load();
	SDL_Surface* GetSDL();
	GLuint GetGL();
	void Draw(double x, double y, bool relative = true, bool flipped = false, double alpha = 1, double angle = 0);
	void operator =(WZLib_PNGProperty* png);
};

void unloadSprites();