////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

int NLS::View::x, NLS::View::y;
double NLS::View::vx, NLS::View::vy;
double NLS::View::tx, NLS::View::ty;
int NLS::View::xmin, NLS::View::xmax, NLS::View::ymin, NLS::View::ymax;
int NLS::View::width = 800, NLS::View::height = 600;
bool NLS::View::relative;

void NLS::View::Init() {
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

void NLS::View::Step() {
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
		srand(Time::tdelta*10000);
		dx += (double)rand()/RAND_MAX*200-100;
		dy += (double)rand()/RAND_MAX*200-100;
		dx *= (double)rand()/RAND_MAX;
		dy *= (double)rand()/RAND_MAX;
	}
	vx += Time::delta*dx*5;
	vy += Time::delta*dy*5;
	if (!Mindfuck and !Map::Login) {
		vx = max(min(vx, mxmax-width), mxmin);
		vy = max(min(vy, mymax-height), mymin);
	}
	x = vx;
	y = vy;
	glLoadIdentity();
	glTranslatef(-x, -y, 0);
	relative = true;
}

void NLS::View::Reset() {
	glLoadIdentity();
	relative = false;
}

void NLS::View::LoginStage(int n) {
	tx = -400;
	ty = (n?-32:12)-600*n;
}

void NLS::View::Follow(int x, int y) {
	tx = x;
	ty = y;
}

void NLS::View::Move(int xx, int yy) {
	tx = xx;
	ty = yy;
	x = vx = tx-width/2;
	y = vy = ty-height/2;
}