////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::AniSprite::AniSprite() {
	frame = 0;
	delay = 0;
	repeat = true;
}

void NLS::AniSprite::Set(Node n) {
	frame = 0;
	delay = 0;
	this->n = n;
	f = n[0];
	a = 1;
}

void NLS::AniSprite::Draw(int x, int y, bool flipped, float rotation) {
	if (!n) {
		return;
	}
	Sprite s = f;
	s.Draw(x, y, flipped, a, rotation);
}

void NLS::AniSprite::Step() {
	if (!n) {
		return;
	}
	delay += Time.delta;
	int d = f["delay"];
	if (d == 0) {
		d = 100;
	}
	if (delay > d) {
		delay  = 0;
		frame++;
		if (!n[frame]) {
			if (repeat) {
				frame = 0;
			} else {
				frame--;
			}
		}
		f = n[frame];
	}
	if (f["a0"] && (!repeat || f["a1"])) {
            double a0 = f["a0"];
            double a1 = f["a1"];
            a = (a0-(a0-a1)*delay/d)/255;
    }
}