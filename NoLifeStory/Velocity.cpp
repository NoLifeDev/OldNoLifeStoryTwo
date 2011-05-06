///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

velocity::velocity() {
	x = 0;
	y = 0;
}

double velocity::xcomp() {
	return x;
}

double velocity::xcomp(double xc) {
	x = xc;
	return x;
}

double velocity::ycomp() {
	return y;
}

double velocity::ycomp(double yc) {
	y = yc;
	return y;
}

double velocity::speed() {
	return pdis(0, 0, x, y);
}

double velocity::speed(double spd) {
	double dir = pdir(0, 0, x, y);
	x = ldx(spd, dir);
	y = ldy(spd, dir);
	return pdis(0, 0, x, y);
}

double velocity::direction() {
	return pdir(0, 0, x, y);
}

double velocity::direction(double dir) {
	double spd = pdis(0, 0, x, y);
	x = ldx(spd, dir);
	y = ldy(spd, dir);
	return pdir(0, 0, x, y);
}
void velocity::add(double spd, double dir) {
	x += ldx(spd, dir);
	y += ldy(spd, dir);
}
void velocity::set(double spd, double dir) {
	x = ldx(spd, dir);
	y = ldy(spd, dir);
}
void velocity::limit(double dir) {
	double ospd = pdis(0, 0, x, y);
	double odir = pdir(0, 0, x, y);
	double spd = ldx(ospd, angdif(odir, dir));
	x = ldx(spd, dir);
	y = ldy(spd, dir);
}

double velocity::getd(double dir) {
	double ospd = pdis(0, 0, x, y);
	double odir = pdir(0, 0, x, y);
	return ldx(ospd, angdif(odir, dir));
}