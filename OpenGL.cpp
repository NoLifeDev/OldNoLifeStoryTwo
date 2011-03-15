///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

GLuint OpenGL::SDL_SurfaceToTexture(Sprite spr) {
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

void OpenGL::drawText(const std::string& str, double x, double y, int size, SDL_Color clrFg) {
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

void OpenGL::drawText(DrawableText &dt) {
	SDL_Surface *sText = TTF_RenderText_Solid(dt.font, dt.text.c_str(), dt.color);
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
	glTranslated(dt.x, dt.y, 0);
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

void OpenGL::drawNameTag(const std::string &name, double x, double y, int tag) {
	int xmin = 0;
	int textheight = 0;
	TTF_SizeText(GetFont("arial", 12), name.c_str(), &xmin, &textheight);
	int w = xmin;
	xmin /= 2;
	int yval = (y + 8) - view.y;
	SDL_Color textColor = OpenGL::getColor(255, 255, 255);
	int start = (x - xmin) - view.x;
	int end = (x + xmin) - view.x;
	if (tag == 0) {
		// Normal tag is just 2 rectangles, but with alpha, so we need to draw 3.
		int h = 15;
		w += 2;
		start -= 1;
		end += 1;

		drawRectangle(start - 1, yval + 1, 1, h - 2, 0, 0, 0, 0.80); // left
		drawRectangle(start, yval, w, h, 0, 0, 0, 0.80); // middle
		drawRectangle(end, yval + 1, 1, h - 2, 0, 0, 0, 0.80); // right
	} else { // Just for you, GOD :p
		Sprite middle = (Sprite)wz::top["UI"]["NameTag"][tostring(tag)]["c"];
		Sprite right = (Sprite)wz::top["UI"]["NameTag"][tostring(tag)]["e"];
		Sprite left = (Sprite)wz::top["UI"]["NameTag"][tostring(tag)]["w"];
		int color = (int)wz::top["UI"]["NameTag"][tostring(tag)]["clr"];
		char red = color >> 24;
		char green = color >> 16;
		char blue = color >> 8;
		char alpha = color;
		textColor = OpenGL::getColor(red, green, blue, alpha);

		for (int i = start; i < end; i += middle.width) {
			middle.Draw(i, yval, false);
		}
		left.Draw(start, yval, false);
		right.Draw(end, yval, false);
		yval = (y - ((middle.height / 2) - (textheight / 2))) - view.y + 8;
	}

	drawText(name, (x - xmin) - view.x, yval, 12, textColor);
	drawText(name, (x - xmin) - view.x, yval, 12, textColor);
}

void OpenGL::drawNPCNameTag(const std::string &name, double x, double y) {
	int xmin = 0;
	int textheight = 0;
	TTF_SizeUTF8(GetFont("arial", 12, TTF_STYLE_BOLD), name.c_str(), &xmin, &textheight);
	int w = xmin;
	xmin /= 2;
	int yval = (y + 8) - view.y;
	int start = (x - xmin) - view.x;
	int end = (x + xmin) - view.x;

	// Normal tag is just 2 rectangles, but with alpha, so we need to draw 3.
	int h = 15;
	w += 2;
	start -= 1;
	end += 1;

	drawRectangle(start - 1, yval + 1, 1, h - 2, 0, 0, 0, 0.80); // left
	drawRectangle(start, yval, w, h, 0, 0, 0, 0.80); // middle
	drawRectangle(end, yval + 1, 1, h - 2, 0, 0, 0, 0.80); // right
	
	DrawableText dt = DrawableText(name, (x - xmin) - view.x, yval, 12, "arial", TTF_STYLE_BOLD);
	dt.color = OpenGL::getColor(255, 255, 0);
	drawText(dt);
}

void OpenGL::drawGuildName(const std::string &name, double x, double y) {
	int xmin = 0;
	TTF_SizeText(GetFont("arial", 12, TTF_STYLE_BOLD), name.c_str(), &xmin, NULL);
	int w = xmin;
	xmin /= 2;
	int yval = (y + 8 + 17) - view.y;
	
	int start = (x - xmin) - view.x;
	int end = (x + xmin) - view.x;
	int h = 15;
	w += 2;
	start -= 1;
	end += 1;

	drawRectangle(start - 1, yval + 1, 1, h - 2, 0, 0, 0, 0.80); // left
	drawRectangle(start, yval, w, h, 0, 0, 0, 0.80); // middle
	drawRectangle(end, yval + 1, 1, h - 2, 0, 0, 0, 0.80); // right

	DrawableText dt = DrawableText(name, (x - xmin) - view.x, yval, 12, "arial", TTF_STYLE_BOLD);
	dt.color = OpenGL::getColor(255, 255, 255);
	drawText(dt);
}