///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

vector<foothold*> footholds;
vector<ladder*> ladders;
///////////////////////////////////////////////////////////////
// Foothold stuff
///////////////////////////////////////////////////////////////
foothold::foothold(double _x1, double _y1, double _x2, double _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
	dir = pdir(x1, y1, x2, y2);
	len = pdis(x1, y1, x2, y2);
	if (dir >= 90 || dir <=-90) {
		walk = false;
	} else {
		walk = true;
	}
	next = 0;
	prev = 0;
	forbid = true;
	footholds.push_back(this);
}

foothold::~foothold() {
	for(auto i = footholds.begin(); i!=footholds.end(); i++) {
		if (*i == this) {
			footholds.erase(i);
		}
	}
}
void foothold::draw() {
	glLoadIdentity();
	glTranslated(-view.x, -view.y, 0);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_LINES);
	{
		glVertex2d(x1, y1);
		glVertex2d(x2, y2);
	}
	glEnd();
}
ladder::ladder() {
	ladders.push_back(this);
}
ladder::~ladder() {
	for(auto i = ladders.begin(); i!=ladders.end(); i++) {
		if (*i == this) {
			ladders.erase(i);
		}
	}
}
void ladder::draw() {
	glLoadIdentity();
	glTranslated(-view.x, -view.y, 0);
	glColor4f(1, 1, 1, 1);
	glBegin(GL_LINES);
	{
		glVertex2d(x, y1);
		glVertex2d(x, y2);
	}
	glEnd();
}