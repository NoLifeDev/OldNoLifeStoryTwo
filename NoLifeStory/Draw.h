///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

// Single delete texture macro
#ifndef glDeleteTexture
#define glDeleteTexture(x) glDeleteTextures(1, x);
#endif

const SDL_Color RectColor = {0, 0, 0, 170};

GLuint SDL_SurfaceToTexture(Sprite spr);

void DrawNameTag(Text* text, double x, double y, int tag);
void DrawGuildName(Text* text, double x, double y, short bg, short bgcolor, short fg, short fgcolor);
void DrawRectangle(int x, int y, int width, int height, SDL_Color color = RectColor);
void DrawNametagRectable(int x, int y, int width, int height, SDL_Color color = RectColor);
SDL_Color GetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
#ifdef DrawText
#undef DrawText
#endif
void DrawText(const std::string &str, double x, double y, int size = 10, SDL_Color color = DefaultTextColor, int style = 0);

inline void DrawRectangle(int x, int y, int width, int height, SDL_Color color) {
	glLoadIdentity();
	glTranslatef(x,y,0);
	glColor4ub(color.r, color.g, color.b, color.unused);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(width, 0);
	glVertex2i(width, height);
	glVertex2i(0, height);
	glEnd();
}
inline void DrawNametagRectable(int x, int y, int width, int height, SDL_Color color) {
	x -= 1;
	width += 1;
	y -= 1;
	height = 16; // test
	DrawRectangle(x-1, y+1, 1, height-2, color);
	DrawRectangle(x, y, width, height, color);
	DrawRectangle(x+width, y+1, 1, height-2, color);
}
inline SDL_Color GetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	SDL_Color color = {r, g, b, a};
	return color;
}