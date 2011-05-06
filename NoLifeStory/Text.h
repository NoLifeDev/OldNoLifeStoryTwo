///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
enum TextAlign {
	ALIGN_LEFT,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

const SDL_Color DefaultTextColor = {255, 255, 255, 255};

class Text {
public:
	Text(const std::string& str, int size, int style = 0);
	void Draw(double x, double y, TextAlign align = ALIGN_CENTER, SDL_Color color = DefaultTextColor);
	~Text();
	int w, h, tw, th;
	GLuint texture;
private:
	Text(const Text&);
};