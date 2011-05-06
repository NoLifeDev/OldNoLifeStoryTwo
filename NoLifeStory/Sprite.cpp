///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

vector<SpriteData*> sprites;

void unload_sprites() {
	for (auto i = sprites.begin(); i != sprites.end(); i++) {
		WZLib_PNGProperty_Unparse((*i)->data);
		(*i)->gltexture = 0;
		(*i)->sdltexture = 0;
		(*i)->loaded = false;
	}
	sprites.clear();
}

SpriteData::SpriteData() {
	gltexture = 0;
	sdltexture = 0;
	loaded = false;
}

Sprite::Sprite() {
	width = 0;
	height = 0;
	twidth = 0;
	theight = 0;
	fwidth = 0;
	fheight = 0;
	originx = 0;
	originy = 0;
	data = 0;
}

void Sprite::Load() {
	sprites.push_back(data);
	data->loaded = true;
	WZLib_PNGProperty_Parse(data->data);
#ifdef WZLIB_USE_GL_DIRECT
	data->gltexture = data->data->png.glTexture;
	data->sdltexture = 0;
#else
	data->sdltexture = data->data->png.sdlsurface;
	if (data->sdltexture == 0) {
		data->gltexture = 0;
	} else {
		data->gltexture = OpenGL::SDL_SurfaceToTexture(*this);
	}
#endif
}

SDL_Surface* Sprite::GetSDL() {
	if (data) {
		if (!data->loaded) {
			Load();
		}
		return data->sdltexture;
	} else {
		return 0;
	}
}

void Sprite::Draw(double x, double y, bool relative, bool flipped, double alpha, double angle) {
	GetGL();
	x = floor(x+0.5);
	y = floor(y+0.5);
	if (angle == 0 && relative) {
		if (flipped) {
			if (x + originx < view.x || y + height- originy < view.y || x - width + originx > view.x + 800 || y - originy > view.y + 600) {
				return;
			}
		} else {
			if (x + width - originx < view.x || y + height-originy < view.y || x - originx > view.x + 800 || y - originy > view.y + 600) {
				return;
			}
		}
	}
	glLoadIdentity();
	glRotated(angle, 0, 0, 1);
	if (flipped) {
		glTranslated(originx-fwidth, -originy, 0);
	} else {
		glTranslated(-originx, -originy, 0);
	}
	double cdir, cdis;
	if (relative) {
		cdir = pdir(0, 0, x-view.x, y-view.y);
		cdis = pdis(0, 0, x-view.x, y-view.y);
	}
	else {
		cdir = pdir(0, 0, x, y);
		cdis = pdis(0, 0, x, y);
	}
	glTranslated(ldx(cdis, cdir-angle), ldy(cdis, cdir-angle), 0);
    glBindTexture(GL_TEXTURE_2D, GetGL());
	glColor4f(1, 1, 1, alpha);
	if (mindfuck) {
		glColor4f(random(1), random(1), random(1), alpha);
	}
    glBegin(GL_QUADS);
	if (flipped) {
		glTexCoord2f(1, 0);
		glVertex2i(0, 0);
		glTexCoord2f(0, 0);
		glVertex2i(fwidth, 0);
		glTexCoord2f(0, 1);
		glVertex2i(fwidth, fheight);
		glTexCoord2f(1, 1);
		glVertex2i(0, fheight);
	} else {
		glTexCoord2f(0, 0);
		glVertex2i(0, 0);
		glTexCoord2f(1, 0);
		glVertex2i(fwidth, 0);
		glTexCoord2f(1, 1);
		glVertex2i(fwidth, fheight);
		glTexCoord2f(0, 1);
		glVertex2i(0, fheight);
	}
    glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
}

GLuint Sprite::GetGL() {
	if (data) {
		if (!data->loaded) {
			Load();
		}
		return data->gltexture;
	} else {
		return 0;
	}
}

void Sprite::operator =(WZLib_PNGProperty* png) {
	data = new SpriteData;
	data->data = png;
}

