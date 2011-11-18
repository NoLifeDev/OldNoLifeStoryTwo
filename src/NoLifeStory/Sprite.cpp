////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

deque <NLS::SpriteData*> NLS::Sprite::loaded;

NLS::Sprite::Sprite() {
	data = 0;
}

void NLS::Sprite::Draw(int x, int y, bool flipped, float alpha, float rotation) {
	if (!data) {
		return;
	}
	if (View.relative && !rotation) {
		if (flipped) {
			if (x+data->originx < View.x ||
				y+data->height-data->originy < View.y ||
				x-data->width+data->originx > View.x+800 ||
				y-data->originy > View.y+600) {
				return;
			}
		} else {
			if (x+data->width-data->originx < View.x ||
				y+data->height-data->originy < View.y ||
				x-data->originx > View.x+800 ||
				y-data->originy > View.y+600) {
				return;
			}
		}
	}
	glPushMatrix();
	glTranslatef(x, y, 0);
	glRotatef(rotation, 0, 0, 1);
	if (flipped) {
		glTranslatef(-data->width+data->originx, -data->originy, 0);
	} else {
		glTranslatef(-data->originx, -data->originy, 0);
	}
	glColor4f(1, 1, 1, alpha);
	if (Mindfuck) {
		srand(floor(Time.tdelta*3)+123456);
		int so = rand();
		srand(floor(Time.tdelta*3)+123457);
		int sn = rand();
		srand(so);
		rand();
		float r = rand()*(1-fmod(Time.tdelta*3, 1));
		float g = rand()*(1-fmod(Time.tdelta*3, 1));
		float b = rand()*(1-fmod(Time.tdelta*3, 1));
		srand(sn);
		rand();
		r += rand()*fmod(Time.tdelta*3, 1);
		g += rand()*fmod(Time.tdelta*3, 1);
		b += rand()*fmod(Time.tdelta*3, 1);
		r /= RAND_MAX;
		g /= RAND_MAX;
		b /= RAND_MAX;
		glColor4f(r, g, b, alpha);
	}
	GetTexture();
	glBegin(GL_QUADS);
	if (flipped) {
		glTexCoord2f(1, 0);
		glVertex2i(0, 0);
		glTexCoord2f(0, 0);
		glVertex2i(data->fw, 0);
		glTexCoord2f(0, 1);
		glVertex2i(data->fw, data->fh);
		glTexCoord2f(1, 1);
		glVertex2i(0, data->fh);
	} else {
		glTexCoord2f(0, 0);
		glVertex2i(0, 0);
		glTexCoord2f(1, 0);
		glVertex2i(data->fw, 0);
		glTexCoord2f(1, 1);
		glVertex2i(data->fw, data->fh);
		glTexCoord2f(0, 1);
		glVertex2i(0, data->fh);
	}
    glEnd();
	glPopMatrix();
}

void NLS::Sprite::GetTexture() {
	static SpriteData* lastData = 0;
	if (data == lastData) {
		return;
	}
	lastData = data;
	if (!data) {
		glBindTexture(GL_TEXTURE_2D, 0);
		return;
	}
	if (!data->loaded) {
		if (!data->png) {
			glBindTexture(GL_TEXTURE_2D, 0);
			return;
		}
		data->png->Parse();
		loaded.push_back(data);
	} else {
		glBindTexture(GL_TEXTURE_2D, data->texture);
	}
}

void NLS::Sprite::Unload() {
	while (loaded.size() > 200) {
		glDeleteTextures(1, &loaded.front()->texture);
		loaded.front()->loaded = false;
		loaded.pop_front();
	}
}
