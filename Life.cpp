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
	state = "";
	f = true;
}

void life::draw() {
	bool noflip = img["info"]["noFlip"] ? (int)img["info"]["noFlip"] : false;
	wz::node data = img[state];
	int d = data[tostring(frame)]["delay"];
	if (d==0) {
		d = 100;
	}
	string type;
	delay += delta;
	if (delay > d) {
		frame += 1;
		if (!data[tostring(frame)]) {
			frame = 0;
			if (!(state == "move" || state == "stand" || state == "fly" || state == "jump")) {
				state = "";
			}
		}
		delay = 0;
	}
	GetNewState();
	data = img[state];

	//TODO Support for more move types
	Sprite spr = data[tostring(frame)];

	bl = x-spr.width/2-5;
	br = x+spr.width/2+5;
	bt = y-spr.height-5;
	bb = y+5;
	
#ifdef _DEBUG
	OpenGL::drawRectangle(bl-view.x, bt-view.y, spr.width + 5, spr.height + 5, 255, 0, 0, 1);
#endif

	spr.Draw(x, y, true, f);
	if (!hidename) {
		OpenGL::drawNPCNameTag(name, x, y - 3);
	}
}

mob::mob() {
	mobs.push_back(this);
}

void mob::GetNewState() {
	if (state == "move" || state == "stand" || state == "fly" || state == "jump") {
		if(random(1)>1-delta/2000) {
			state = ""; // FIX THIS
		}
	}
	if(state==""){
		
	}
}

npc::npc() {
	npcs.push_back(this);
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
	z = depth::layer;
	z = 8;
	z = depth::life;
	name = (string)wz::top["String"]["Mob"][tostring(id)]["name"];
	state = "stand";
}