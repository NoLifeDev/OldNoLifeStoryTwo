///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

deque <object*> objects;
vector <portal*> portals;

///////////////////////////////////////////////////////////////
// The base object class
///////////////////////////////////////////////////////////////
object::object() {
	objects.push_back(this);
	x = 0;
	y = 0;
}

object::~object() {
	objects.erase(find(objects.begin(), objects.end(), this));
}
///////////////////////////////////////////////////////////////
// Tiles
///////////////////////////////////////////////////////////////
tile::tile() {
}
void tile::draw() {
	spr.Draw(x, y);
}
///////////////////////////////////////////////////////////////
// Portals
///////////////////////////////////////////////////////////////
portal::portal() {
	portals.push_back(this);
	frame = 0;
	delay = 0;
	close = false;
	ani = 3;
}
void portal::draw() {
	Sprite spr;
	wz::node fdata;
	int d;
	switch (pt) {
	case 0:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["sp"];
			spr = fdata;
		}
		break;
	case 1:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pi"];
			spr = fdata;
		}
		break;
	case 2:
		delay += delta;
		d = 100;
		if (delay > d) {
			frame += 1;
			if (frame == 8) {
				frame = 0;
			}
			delay = 0;
		}
		fdata = wz::top["Map"]["MapHelper"]["portal"]["game"]["pv"][tostring(frame)];
		spr = fdata;
		break;
	case 3:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pc"];
			spr = fdata;
		}
		break;
	case 4:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pg"];
			spr = fdata;
		}
		break;
	case 5:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pgi"];
			spr = fdata;
		}
		break;
	case 6:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["tp"];
			spr = fdata;
		}
		break;
	case 7:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["ps"];
			spr = fdata;
		}
		break;
	case 8:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["psi"];
			spr = fdata;
		}
		break;
	case 9:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pcs"];
			spr = fdata;
		}
		break;
	case 10:
		{
			int f = 0;
			string type;
			delay += delta;
			d = 100;
			if (delay > d) {
				frame += 1;
				delay = 0;
			}
			if (ani == 3 && close == true) {
				frame = 0;
				delay = 0;
				type = "portalStart";
				ani = 0;
			}
			if (ani == 0) {
				if (frame >= 4) {
					f = 6;
					frame = 0;
					delay = 0;
					type = "portalContinue";
					ani = 1;
				} else {
					type = "portalStart";
				}
			}
			if (ani == 1) {
				if (close == false) {
					frame = 0;
					delay = 0;
					type = "portalExit";
					ani = 2;
				} else {
					f = 6;
					type = "portalContinue";
				}
			}
			if (ani == 2) {
				if (frame >= 3) {
					ani = 3;
				} else {
					type = "portalExit";
				}
			}
			if (frame > f && f!=0) {
				frame = 0;
			}
			fdata = wz::top["Map"]["MapHelper"]["portal"]["game"]["ph"]["default"][type][tostring(frame)];
			spr = fdata;
		}
		break;
	case 11:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["psh"];
			spr = fdata;
		}
		break;
	case 12:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pcj"];
			spr = fdata;
		}
		break;
	case 13:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pci"];
			spr = fdata;
		}
		break;
	case 14:
		if (Game::DevPortals) {
			fdata = wz::top["Map"]["MapHelper"]["portal"]["editor"]["pcig"];
			spr = fdata;
		}
		break;
	}
	spr.Draw(x, y);
}
///////////////////////////////////////////////////////////////
// Objects
///////////////////////////////////////////////////////////////
obj::obj() {
	delay = 0;
	frame = 0;
}
void obj::draw() {
	double ax, ay;
	ax = 0;
	ay = 0;
	double ang = 0;
	if (movetype)
	switch(movetype) {
	case 1:
		if (movep) {
			ax = movew*sin(double(tdelta)*2*PI/movep);
		} else {
			ax = movew*sin(double(tdelta)/1000);
		}
		break;
	case 2:
		if (movep) {
			ay = moveh*sin(double(tdelta)*2*PI/movep);
		} else {
			ay = moveh*sin(double(tdelta)/1000);
		}
		break;
	case 3:
		ang = double(tdelta)/mover*radtodeg;
		break;
	};
	delay += delta;
	int d = data[tostring(frame)]["delay"];
	if (d == 0) {
		d = 100;
	}
	double a = 255;
	if (delay > d) {
		frame += 1;
		if (!data[tostring(frame)]) {
			if (!repeat) {
				frame = 0;
			} else {
				frame -= 1;
			}
		}
		delay = 0;
	}
	wz::node fdata = data[tostring(frame)];
	spr = fdata;
	if (fdata["a0"] && (!repeat || fdata["a1"])) {
		double a0 = fdata["a0"];
		double a1 = fdata["a1"];
		a = a0-(a0-a1)*delay/d;
	}
	switch(flow) {
	case 0:
		spr.Draw(x+ax, y+ay, true, f, a/255, ang);
		break;
	case 1:
		x += rx*double(delta)/1000*5;
		double cx = view.xmax - view.xmin;
		for(int i=fmod(x-view.x, cx)-cx+view.x;i<view.x+800+cx;i+=cx) {
			spr.Draw(i+ax, y+ay, true, f, a/255, ang);
		}
		break;
	}
}
///////////////////////////////////////////////////////////////
// Backgrounds
///////////////////////////////////////////////////////////////
back::back() {
	delay = 0;
	frame = 0;
}

// Macros to minify code
#define DRAWHOR\
		for(int i=fmod(x-view.x+ox+orx, cx)-cx+view.x-ox;i+ox<view.x+800+cx+orx;i+=cx) {\
			spr.Draw(i+ox+ax, y+oy+ay, true, f, a/255, ang);\
		}
#define DRAWVERT\
		for(int j=fmod(y-view.y+oy+ory, cy)-cy+view.y-oy;j+oy<view.y+600+cy+ory;j+=cy) {\
			spr.Draw(x+ox+ax, j+oy+ay, true, f, a/255, ang);\
		}
#define DRAWBOTH\
		for(int i=fmod(x-view.x+ox+orx, cx)-cx+view.x-ox;i+ox<view.x+800+cx+orx;i+=cx) {\
			for(int j=fmod(y-view.y+oy+ory, cy)-cy+view.y-oy;j+oy<view.y+600+cy+ory;j+=cy) {\
				spr.Draw(i+ox+ax, j+oy+ay, true, f, a/255, ang);\
			}\
		}

void back::draw() {
	double a = 255;
	double ax = 0;
	double ay = 0;
	double ang = 0;
	if (movetype)
	switch(movetype) {
	case 1:
		if (movep) {
			ax = movew*sin(double(tdelta)*2*PI/movep);
		} else {
			ax = movew*sin(double(tdelta)/1000);
		}
		break;
	case 2:
		if (movep) {
			ay = moveh*sin(double(tdelta)*2*PI/movep);
		} else {
			ay = moveh*sin(double(tdelta)/1000);
		}
		break;
	case 3:
		ang = double(tdelta)/mover*radtodeg;
		break;
	};
	if (ani) {
		delay += delta;
		int d = data[tostring(frame)]["delay"];
		if (d == 0) {
			d = 100;
		}
		if (delay > d) {
			frame += 1;
			if (!data[tostring(frame)]) {
				frame = 0;
			}
			delay = 0;
		}
		wz::node fdata = data[tostring(frame)];
		spr = fdata;
		if (fdata["a0"] || fdata["a1"]) {
			double a0 = fdata["a0"];
			double a1 = fdata["a1"];
			a = a0-(a0-a1)*delay/d;
		}
		if (cx == 0) {
			cx = fdata["width"];
		}
		if (cy == 0) {
			cy = fdata["height"];
		}
	}
	double ox = double(100+rx)/100*(view.x+400);
	double oy = double(100+ry)/100*(view.y+300);
	int orx = spr.originx-spr.originx%cx;
	int ory = spr.originy-spr.originy%cy;
	switch(type) {
	case 0:
		spr.Draw(x+ox+ax, y+oy+ay, true, f, a/255, ang);
		break;
	case 1:
		if (cx == 0) {return;}
		DRAWHOR
		break;
	case 2:
		if (cy == 0) {return;}
		DRAWVERT
		break;
	case 3:
		if (cx == 0 || cy == 0) {return;}
		DRAWBOTH
		break;
	case 4:
		x += double(rx*double(delta))/1000*5;
		if (cx == 0) {return;}
		DRAWHOR
		break;
	case 5:
		y += double(ry*double(delta))/1000*5;
		if (cy == 0) {return;}
		DRAWVERT
		break;
	case 6:
		x += double(rx*double(delta))/1000*5;
		if (cx == 0 || cy == 0) {return;}
		DRAWBOTH
		break;
	case 7:
		y += double(ry*double(delta))/1000*5;
		if (cx == 0 || cy == 0) {return;}
		DRAWBOTH
		break;
	default:
		break;
	}
}

#undef DRAWHOR
#undef DRAWVERT
#undef DRAWBOTH