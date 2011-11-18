////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::_View NLS::View;

NLS::_View::_View() {
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
	width = 800;
	height = 600;
}

void NLS::_View::Step() {
	double mxmax = xmax;
	double mxmin = xmin;
	double mymax = ymax;
	double mymin = ymin;
	if (mymax-mymin < height) {
		int dif = height-(mymax-mymin);
		mymax += dif/2;
		mymin -= dif/2;
	}
	if (mxmax-mxmin < width) {
		int dif = width-(mxmax-mxmin);
		mxmax += dif/2;
		mxmin -= dif/2;
	}

	double ttx = tx-width/2;
	double tty = ty-height/2;
	double dx = ttx-vx;
	double dy = tty-vy;
	dx = max(abs(dx)-20, 0.0)*sign(dx);
	dy = max(abs(dy)-20, 0.0)*sign(dy);
	if (Mindfuck) {
		dx += (double)rand()/RAND_MAX*200-100;
		dy += (double)rand()/RAND_MAX*200-100;
		dx *= (double)rand()/RAND_MAX;
		dy *= (double)rand()/RAND_MAX;
	}
	vx += Time.delta*dx*5;
	vy += Time.delta*dy*5;
	if (!Mindfuck) {
		vx = max(min(vx, mxmax-width), mxmin);
		vy = max(min(vy, mymax-height), mymin);
	}
	x = vx;
	y = vy;
	glLoadIdentity();
	glTranslatef(-x, -y, 0);
	relative = true;
}

void NLS::_View::Reset() {
	glLoadIdentity();
	relative = false;
}