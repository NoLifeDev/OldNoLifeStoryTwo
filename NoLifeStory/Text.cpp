///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

vector<GLuint> texts;

Text::Text(const std::string& str, int size, int style) {
	SDL_Surface *sText = TTF_RenderText_Blended(GetFont("arial", size), str.c_str(), GetColor(255,255,255,255));
	Uint32 rmask, gmask, bmask, amask;
	SDL_Surface * temp = NULL;
	SDL_Surface * tempalpha = NULL;
	tw = 2;
	th = 2;
	w = sText->w;
	h = sText->h;
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
	//Is it possible to eliminate some of this surface work?
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, NULL);
	SDL_FreeSurface(sText);
}

void Text::Draw(double x, double y, TextAlign align, SDL_Color color) {
	switch(align) {
	case ALIGN_LEFT:
		//Do nothing
		break;
	case ALIGN_CENTER:
		x -= w/2;
		break;
	case ALIGN_RIGHT:
		x -= w;
		break;
	}
	glBindTexture(GL_TEXTURE_2D, texture);
	glLoadIdentity();
    glTranslated(x,y,0);
	glColor4ub(color.r,color.g,color.b,color.unused);
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
	glBindTexture(GL_TEXTURE_2D, NULL);
}

Text::~Text() {
	glDeleteTexture(&texture);
}