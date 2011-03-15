///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

void DrawText(const std::string& str, double x, double y, int size, SDL_Color clrFg) {
	SDL_Surface *sText = TTF_RenderText_Solid(GetFont("arial", size), str.c_str(), clrFg);
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