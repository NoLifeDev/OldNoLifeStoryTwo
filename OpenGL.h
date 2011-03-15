///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

// Single delete texture macro
#ifndef glDeleteTexture
#define glDeleteTexture(x) glDeleteTextures(1, x);
#endif

struct DrawableText;

namespace OpenGL {
	GLuint SDL_SurfaceToTexture(Sprite spr);

	SDL_Color getColor(double red, double green, double blue, double alpha = 0);
	void drawText(const std::string &str, double x, double y, int size = 10, SDL_Color clrFg = OpenGL::getColor(0, 0, 255));
	void drawText(DrawableText &dt);
	void drawNameTag(const std::string &name, double x, double y, int tag);
	void drawNPCNameTag(const std::string &name, double x, double y);
	void drawGuildName(const std::string &name, double x, double y);
	void drawRectangle(int x, int y, int width, int height, double red = 0, double green = 0, double blue = 0, double alpha = 1);
};

struct DrawableText {
	DrawableText(const string &text, double x, double y, int size = 12, string font = "arial", int style = TTF_STYLE_NORMAL) :
	text(text), x(x), y(y), size(size), color(OpenGL::getColor(0, 0, 0)), font(GetFont(font, size, style))
	{ };
	string text;
	double x;
	double y;
	int size;
	SDL_Color color;
	TTF_Font *font;
};

inline SDL_Color OpenGL::getColor(double red, double green, double blue, double alpha) {
	SDL_Color color = {red, green, blue, alpha};
	return color;
}

inline void OpenGL::drawRectangle(int x, int y, int width, int height, double red, double green, double blue, double alpha) {
	glLoadIdentity();
	glColor4d(red, green, blue, alpha);
	glBegin(GL_QUADS);
	glVertex2i(x, y);
	glVertex2i(x + width, y);
	glVertex2i(x + width, y + height);
	glVertex2i(x, y + height);
	glEnd();
}