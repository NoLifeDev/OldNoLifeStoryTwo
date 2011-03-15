///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

view_class::view_class() {
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	tx = 0;
	ty = 0;
	xmin = 0;
	xmax = 0;
	ymin = 0;
	ymax = 0;
}
void view_class::step() {
	double dx = tx-vx;
	double dy = ty-vy;
	dx = max(abs(dx)-20,(double)0)*sign(dx);
	dy = max(abs(dy)-20,(double)0)*sign(dy);
	vx += delta*dx/200;
	vy += delta*dy/200;
	vx = max(min(vx,xmax-800),xmin);
	vy = max(min(vy,ymax-600),ymin);
	x = vx;
	y = vy;
}
view_class view;