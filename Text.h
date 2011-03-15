///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

class Text {
	Text(const std::string& str, int size, SDL_Color clrFg);
	void Draw(double x, double y);
	~Text();
};

void DrawText(const std::string& str, double x, double y, int size, SDL_Color clrFg);