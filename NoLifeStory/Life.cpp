///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

vector <life*> lifes;
vector <mob*> mobs;
vector <npc*> npcs;
///////////////////////////////////////////////////////////////
// The base life class
///////////////////////////////////////////////////////////////
life::life() {
	lifes.push_back(this);
	x = 0;
	y = 0;
	frame = 0;
	delay = 0;
	ldelay = 0;
	tname = 0;
	state = "";
	f = true;
}

void life::draw() {
	bool noflip = img["info"]["noFlip"] ? (int)img["info"]["noFlip"] : false;
	wz::node data = img[state];
	int d = data[tostring(frame)]["delay"];
	if (d == 0) {
		d = 100;
	}
	
	delay += delta;
	if (delay > d) {
		frame += 1;
		if (!data[tostring(frame)]) {
			frame = 0;
			GetNewState();
		}
		delay = 0;
	}
	data = img[state];

	//TODO Support for more move types
	Sprite spr = data[tostring(frame)];

	bl = x-spr.width/2-5;
	br = x+spr.width/2+5;
	bt = y-spr.height-5;
	bb = y+5;
	spr.Draw(x, y, true, f);
}

void mob::draw() {
	life::draw();
	if (!hidename) {
		if (!tname) {
			tname = new Text(name, 12);
		}
		int yval = y+8-view.y;
		int start = x-tname->w/2-view.x;
		DrawNametagRectable(start, yval, tname->w, tname->h);
		tname->Draw(x, yval, ALIGN_CENTER, GetColor(255, 255, 0, 0));
		//Need to draw the level as well
	}
}

void npc::draw() {
	life::draw();
	if (!hidename) {
		if (!tname) {
			tname = new Text(name, 12, 1);
		}
		int yval = y+8-view.y;
		int start = x-tname->w/2-view.x;
		DrawNametagRectable(start, yval, tname->w, tname->h);
		tname->Draw(x, yval, ALIGN_CENTER, GetColor(255, 255, 0, 0));
		//Need to draw the NPC's job underneath as well
	}
}

void mob::GetNewState() {
	if (state == "move" || state == "stand" || state == "fly" || state == "jump") {
		if (random(1) > 1-double(delta)/2000) {
			state = ""; // FIX THIS
		}
	} else {
		state = "";
	}
	if (state == "") {
		
	}
}

void npc::GetNewState() {
	if (usableStates.size() == 0) {
		// Load all usable states.
		for (auto i = img.begin(); i != img.end(); i++) {
			if (i->first == "info") {
				continue;
			}
			usableStates.push_back(i->first);
		}
	}
	int i = random(usableStates.size());
	state = usableStates[i];
}

mob::mob() {
	mobs.push_back(this);
}

npc::npc() {
	npcs.push_back(this);
}


void mob::init() {
	wz::node info = img["info"];
	acc = info["acc"];
	bodyAttack = info["bodyAttack"];
	category = img["category"];
	eva = info["eva"];
	exp = info["exp"];
	fs = info["fs"];
	level = info["level"];
	MADamage = info["MADamage"];
	maxHP = info["maxHP"];
	maxMP = info["maxMP"];
	MMDamage = info["MMDamage"];
	PADamage = info["PADamage"];
	PDDamage = info["PDDamage"];
	pushed = info["pushed"];
	speed = info["speed"];
	summonType = info["summonType"];
	undead = info["undead"];
	hidename = (bool)(int)info["hideName"];
	boss = (bool)(int)info["boss"];
	if (boss) hidename = true;
	z = depth::layer;
	z = 8;
	z = depth::life;
	name = (string)wz::top["String"]["Mob"][tostring(id)]["name"];
	state = "stand";
}