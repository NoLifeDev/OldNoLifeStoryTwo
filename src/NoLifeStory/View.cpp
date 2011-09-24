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
	if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Up)) {
		ty -= Time.delta;
	}
	if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Down)) {
		ty += Time.delta;
	}
	if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left)) {
		tx -= Time.delta;
	}
	if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right)) {
		tx += Time.delta;
	}
	int mxmax = xmax;
	int mxmin = xmin;
	int mymax = ymax;
	int mymin = ymin;
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
	tx = max(min(tx, mxmax-width+30), mxmin-30);
	ty = max(min(ty, mymax-height+30), mymin-30);
	double dx = tx-vx;
	double dy = ty-vy;
	dx = max(abs(dx)-20, 0.0)*sign(dx);
	dy = max(abs(dy)-20, 0.0)*sign(dy);
	vx += Time.delta*dx/200;
	vy += Time.delta*dy/200;
	vx = max(min(vx, mxmax-width), mxmin);
	vy = max(min(vy, mymax-height), mymin);
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