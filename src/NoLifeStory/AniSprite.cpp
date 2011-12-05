////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::AniSprite::AniSprite() {
	frame = 0;
	delay = 0;
	repeat = true;
	zigzag = false;
	up = true;
	done = false;
}

void NLS::AniSprite::Set(Node n) {
	frame = 0;
	delay = 0;
	this->n = n;
	f = n[0];
	a = 1;
	up = true;
	done = false;
	zigzag = !!n["zigzag"];
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
	delay += Time::delta*1000;
	int d = f["delay"];
	if (d == 0) {
		d = 100;
	}
	if (delay > d) {
		delay = 0;
		if (zigzag) {
			if (up) frame++;
			else frame--;
			if (!n[frame]) {
				if (repeat) {
					if (up) {
						frame--;
						up = false;
					}
					else {
						frame = 0;
						up = true;
					}
				}
				else {
					frame--;
				}
			}
		}
		else {
			frame++;
			if (!n[frame]) {
				if (repeat) {
					frame = 0;
				} 
				else {
					frame--;
					done = true;
				}
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