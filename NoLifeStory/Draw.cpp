///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

GLuint SDL_SurfaceToTexture(Sprite spr) {
	Uint32 rmask, gmask, bmask, amask;
	SDL_Surface * temp = NULL;
	SDL_Surface * tempalpha = NULL;
	GLuint texture;
	int tw, th;
	tw = spr.fwidth;
	th = spr.fheight;
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	tempalpha = SDL_DisplayFormatAlpha(spr.data->sdltexture);
	SDL_FreeSurface(spr.data->sdltexture);
	spr.data->sdltexture = 0;
	SDL_SetAlpha(tempalpha, 0, SDL_ALPHA_TRANSPARENT);
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE, tw, th,
								32, bmask, gmask, rmask, amask);
	SDL_BlitSurface(tempalpha, NULL, temp, NULL);
	
	SDL_FreeSurface(tempalpha);
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	SDL_LockSurface(temp);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tw, th, 0, GL_BGRA, GL_UNSIGNED_BYTE, temp->pixels);
	SDL_UnlockSurface(temp);
	SDL_FreeSurface(temp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return texture;
}

void DrawNameTag(Text* text, double x, double y, int tag) {
	int yval = y+2-view.y;
	int start = x-text->w/2-view.x;
	int end = x+text->w/2-view.x;
	SDL_Color color = DefaultTextColor;
	if (tag == 0) {
		DrawNametagRectable(start, yval, text->w, text->h);
	} else {
		Sprite middle = (Sprite)wz::top["UI"]["NameTag"][tostring(tag)]["c"];
		Sprite right = (Sprite)wz::top["UI"]["NameTag"][tostring(tag)]["e"];
		Sprite left = (Sprite)wz::top["UI"]["NameTag"][tostring(tag)]["w"];
		int icolor = (int)wz::top["UI"]["NameTag"][tostring(tag)]["clr"];
		color.r = icolor >> 24;
		color.g = icolor >> 16;
		color.b = icolor >> 8;
		color.unused = icolor;
		for (int i = start; i < end; i += middle.width) {
			middle.Draw(i, yval, false);
		}
		left.Draw(start, yval, false);
		right.Draw(end, yval, false);
		yval = y-middle.height/2+text->h/2-view.y+8;
	}
	text->Draw(x-view.x, yval, ALIGN_CENTER, color);
}

void DrawGuildName(Text* text, double x, double y, short bg, short bgcolor, short fg, short fgcolor) {
	int yval = y+19-view.y;
	int start = x-text->w/2-view.x;
	int end = x+text->w/2-view.x;
	DrawNametagRectable(start, yval, text->w, text->h);
	text->Draw(x-view.x, yval, ALIGN_CENTER);
	if (bg or bgcolor) {
		Sprite icon = wz::top["UI"]["GuildMark"]["BackGround"]["0000"+tostring(bg)][tostring(bgcolor)];
		icon.Draw(start-3-icon.width, yval-1, false);
	}
	if (fg or fgcolor) {
		string imgname = "";
		int type = fg/1000;
		switch (type) {
			case 2: imgname = "Animal"; break;
			case 3: imgname = "Plant"; break;
			case 4: imgname = "Pattern"; break;
			case 5: imgname = "Letter"; break;
			case 9: imgname = "Etc"; break;
		}
		Sprite icon = (Sprite)wz::top["UI"]["GuildMark"]["Mark"][imgname]["0000"+tostring(fg)][tostring(fgcolor)];
		icon.Draw(start-5-icon.width, yval, false);
	}
}

void DrawText(const std::string &str, double x, double y, int size, SDL_Color color, int style) {
	SDL_Surface *sText = TTF_RenderText_Solid(GetFont("arial", size), str.c_str(), color);
	Uint32 rmask, gmask, bmask, amask;
	SDL_Surface * temp = NULL;
	SDL_Surface * tempalpha = NULL;
	GLuint texture;
	int tw = 2, th = 2;
	while (tw < sText->w) {
		tw *= 2;
	}
	while (th < sText->h) {
		th *= 2;
	}
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	tempalpha = SDL_DisplayFormatAlpha(sText);
	SDL_SetAlpha(tempalpha, 0, SDL_ALPHA_TRANSPARENT);
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE, tw, th, 32, bmask, gmask, rmask, amask);
	SDL_BlitSurface(tempalpha, NULL, temp, NULL);
	
	SDL_FreeSurface(tempalpha);
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	SDL_LockSurface(temp);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tw, th, 0, GL_BGRA, GL_UNSIGNED_BYTE, temp->pixels);
	SDL_UnlockSurface(temp);
	SDL_FreeSurface(temp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// DRAW
	glLoadIdentity();
    glTranslated(x,y,0);
    glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1,1,1,1);
    glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2i(0, 0);
		glTexCoord2f(1, 0);
		glVertex2i(tw, 0);
		glTexCoord2f(1, 1);
		glVertex2i(tw, th);
		glTexCoord2f(0,1);
		glVertex2i(0, th);
	}
    glEnd();
	glDeleteTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, NULL);
	SDL_FreeSurface(sText);
}