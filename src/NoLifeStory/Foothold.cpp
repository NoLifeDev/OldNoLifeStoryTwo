////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set <NLS::Foothold*> NLS::Foothold::All;

void NLS::Foothold::Load(Node n) {
	for_each(begin(), end(), [](Foothold* fh){delete fh;});
	All.clear();
	n = n["foothold"];
	if (!n) return;
	for (auto i = n.begin(); i != n.end(); i++) {
		int fhdepth = toint(i->first);
		for (auto j = i->second.begin(); j != i->second.end(); j++) {
			int fhgroup = toint(j->first);
			for (auto k = j->second.begin(); k != j->second.end(); k++) {
				Node fn = k->second;
				Foothold* fh = new Foothold();
				fh->x1 = fn["x1"];
				fh->y1 = fn["y1"];
				fh->x2 = fn["x2"];
				fh->y2 = fn["y2"];
				fh->nextid = fn["next"];
				fh->previd = fn["prev"];
				fh->force = fn["force"];
				fh->forbid = (int)fn["forbidFallDown"];
				fh->id = toint(k->first);
				fh->layer = fhdepth;
				fh->group = fhgroup;
				fh->dir = pdir(fh->x1, fh->y1, fh->x2, fh->y2);
				fh->len = pdis(fh->x1, fh->y1, fh->x2, fh->y2);
				fh->walk = fh->x2>fh->x1;
				fh->next = 0;
				fh->prev = 0;
				All.insert(fh);
			}
		}
	}
	for_each(begin(), end(), [](Foothold* fh1){
		for_each(begin(), end(), [&](Foothold* fh2){
			if (fh1->nextid == fh2->id) {
				fh1->next = fh2;
			}
			if (fh1->previd == fh2->id) {
				fh1->prev = fh2;
			}
		});
	});
}

void NLS::Foothold::Draw() {
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_LINES);
	for_each(begin(), end(), [](Foothold* lr){
		glVertex2f(lr->x1, lr->y1);
		glVertex2f(lr->x2, lr->y2);
	});
	glEnd();
}