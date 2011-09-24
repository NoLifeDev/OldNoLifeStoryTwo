////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set <NLS::Foothold*> NLS::footholds;

void NLS::Foothold::Load(Node n) {
	for (auto i = footholds.begin(); i != footholds.end(); i++) {
		delete *i;
	}
	footholds.clear();
	n = n["foothold"];
	if (!n) {
		C("ERROR") << "No foothold node" << endl;
		throw(273);
	}
	for (auto i = n.Begin(); i != n.End(); i++) {
		int fhdepth = toint(i->first);
		for (auto j = i->second.Begin(); j != i->second.End(); j++) {
			int fhgroup = toint(j->first);
			for (auto k = j->second.Begin(); k != j->second.End(); k++) {
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
				fh->walk = fh->dir < 90 and fh->dir > -90;
				fh->next = 0;
				fh->prev = 0;
				footholds.insert(fh);
			}
		}
	}
	for (auto i = footholds.begin(); i != footholds.end(); i++) {
		for (auto j = footholds.begin(); j != footholds.end(); j++) {
			auto fi = *i;
			auto fj = *j;
			if (fi->nextid == fj->id) {
				fi->next = fj;
			}
			if (fi->previd == fj->id) {
				fi->prev = fj;
			}
		}
	}
}

void NLS::Foothold::Draw() {
	glPushMatrix();
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBegin(GL_LINES);
	for (auto i = footholds.begin(); i != footholds.end(); i++) {
		glVertex2f((*i)->x1, (*i)->y1);
		glVertex2f((*i)->x2, (*i)->y2);
	}
	glEnd();
	glPopMatrix();
}