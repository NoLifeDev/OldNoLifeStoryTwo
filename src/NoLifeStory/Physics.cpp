////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

const double walkForce = 140000;
const double walkSpeed = 125;
const double walkDrag = 80000;
const double slipForce = 60000;
const double slipSpeed = 120;
const double floatDrag1 = 100000;
const double floatDrag2 = 10000;
const double floatCoefficient = 0.01;
const double swimForce = 120000;
const double swimSpeed = 140;
const double flyForce = 120000;
const double flySpeed = 200;
const double gravityAcc = 2000;
const double fallSpeed = 670;
const double jumpSpeed = 555;
const double maxFriction = 2;
const double minFriction = 0.05;
const double swimSpeedDec = 0.9;
const double flyJumpDec = 0.35;
const double wat1 = 0.0008928571428571428;

void NLS::Physics::Init() {
	Node n = WZ["Map"]["Physics"];//TODO - Load this?
}

NLS::Physics::Physics() {
	Reset(0, 0);
}

NLS::Physics::Physics(double x, double y) {
	Reset(x, y);
}

void NLS::Physics::Reset(double x, double y) {
	this->x = x;
	this->y = y;
	r = 0;
	vx = 0;
	vy = 0;
	vr = 0;
	fh = nullptr;
	lr = nullptr;
	layer = 0;
	group = 0;
	freefall = 0;
}

void NLS::Physics::Update() {
	double mass = 100;//TODO - Add proper shoe stuff
	//TODO - Move this control stuff elsewhere
	bool left = sf::Keyboard::IsKeyPressed(sf::Keyboard::Left);
	bool right = sf::Keyboard::IsKeyPressed(sf::Keyboard::Right);
	bool up = sf::Keyboard::IsKeyPressed(sf::Keyboard::Up);
	bool down = sf::Keyboard::IsKeyPressed(sf::Keyboard::Down);
	//TODO - Handle jumping here
	//Movement and friction
	if (fh) {//Walking on the ground

	} else {//Not on the ground
		if (false) {//Underwater

		} else {//Just mid-air
			if (vy > 0.) {//First vertical air friction
				vy = max(0., vy-floatDrag2/mass*Time.delta);
			} else {
				vy = min(0., vy+floatDrag2/mass*Time.delta);
			}
			vy += gravityAcc*Time.delta;//Then gravity
			vy = max(min(vy, fallSpeed), -fallSpeed);//Then keep speed within the limit
			if (left^right) {//Trying to move left or right
				double l = floatDrag2*wat1;
				if (left) {
					if (vx > -l) {
						vx = max(-l, vx-floatDrag2*2/mass*Time.delta);
					}
				} else {
					if (vx < l) {
						vx = min(l, vx+floatDrag2*2/mass*Time.delta);
					}
				}
			} else {//Just falling
				if (vy < fallSpeed) {
					if (vx > 0) {
						vx = max(0., vx-floatDrag2*floatCoefficient*Time.delta);
					} else {
						vx = min(0., vx+floatDrag2*floatCoefficient*Time.delta);
					}
				} else {
					if (vx > 0) {
						vx = max(0., vx-floatDrag2*Time.delta);
					} else {
						vx = min(0., vx+floatDrag2*Time.delta);
					}
				}
			}
		}
		//Detect collisions
	}
	//TODO - Grab on to ladders
	//Collision Detection
	if (fh) {

	} else if (!lr) {
		double xp = x;
		double yp = y;
		x += vx*Time.delta;
		y += vy*Time.delta;
		double dis = pdis(vx, vy)*Time.delta;
		double dir = pdir(vx, vy);
		for (auto it = footholds.begin(); it != footholds.end(); it++) {
			Foothold& o = **it;
			if (!o.walk && group != o.group) continue;
			if (angdif(dir, o.dir) < 0) continue;
			if (angdif(dir, pdir(xp, yp, o.x1, o.y1)) > 0) continue;
			if (angdif(dir, pdir(xp, yp, o.x2, o.y2)) < 0) continue;
			double dt = ldy(pdis(xp, yp, o.x1, o.y1), angdif(o.dir, pdir(o.x1, o.y1, xp, yp)));
			double d = dt/cos(degtorad*angdif(dir, o.dir+90));
			if (d < 0 or d > dis) continue;
			fh = &o;
			dis = d;
		}
		if (fh) {
			vr = ldx(pdis(vx, vy), dir);
			x = xp+ldx(dis, dir);
			y = yp+ldy(dis, dir);
			r = pdis(fh->x1, fh->y1, x, y);
			group = fh->group;
			layer = fh->layer;
		}
	}
	//Various bounds and coordinate transformations
	if (fh) {
		//Turn r into x, y
	} else if (lr) {
		//Turn r into x, y
	} else {
		if (vy < fallSpeed) {
			freefall = 0;
		} else {
			freefall += Time.delta;
		}
		if (y >= View.ymax and vy > 0) {
			vy = 0;
			y = View.ymax;
		}
	}
}

void NLS::Physics::MouseFly() {
	auto p = sf::Mouse::GetPosition(*window);
	Reset(p.x+View.x, p.y+View.y);
}