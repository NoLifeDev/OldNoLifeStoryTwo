///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

map<string, TTF_Font *> fonts;

TTF_Font* GetFont(const string &name, int size, int style) {
	string mapname = name+"_"+tostring(size)+"_"+tostring(style);
	if (fonts[mapname] == nullptr) {
		TTF_Font *font = TTF_OpenFont((name+".ttf").c_str(), size);
		TTF_SetFontStyle(font, style);
		fonts[mapname] = font;
	}
	return fonts[mapname];
}