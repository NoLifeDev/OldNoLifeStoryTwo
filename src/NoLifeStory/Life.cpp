////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

map <uint32_t, NLS::Mob *> NLS::Life::Mobs;
map <uint32_t, NLS::Npc *> NLS::Life::Npcs;

uint32_t NLS::Life::NpcStart = 100;
uint32_t NLS::Life::MobStart = 0;

void NLS::Life::Load() {
	NpcStart = 100;
	MobStart = 0;

	for (auto it = Mobs.begin(); it != Mobs.end(); it++) {
		delete it->second;
	}
	Mobs.clear();
	for (auto it = Npcs.begin(); it != Npcs.end(); it++) {
		delete it->second;
	}
	Npcs.clear();

	Node data = Map::node["life"];
	if (!data || Network::Connected) return;
	
	for (auto it = data.begin(); it != data.end(); it++) {
		Node rn = it->second;
		Life* r;
		string type = (string) rn["type"];
		if (type == "n")	{
			r = new Npc;
		}
		else if (type == "m") {
			r = new Mob;
		}
		else {
			cerr << "[WARN] Loading unknown 'life'! Map: " << Map::curmap << ", Life list ID: " << it->first << ", Type: " << r->type << endl;
			// Safe mode, Erwin style
			//  delete r;
			//  continue;
			// Rage mode, Peter style
			throw(273); // Goodbye cruel world.
		}
		r->id = (string)rn["id"];
		r->x = rn["x"];
		r->y = rn["y"];
		r->cx = rn["cx"];
		r->cy = rn["cy"];
		r->rx0 = rn["rx0"];
		r->rx1 = rn["ry1"];
		r->f = (int)rn["f"];
		r->time = rn["mobTime"];
		r->Init();
		r->Reset(r->x, r->y);
		if (r->type == "n") Npcs[NpcStart++] = (NLS::Npc*)r;
		else if (r->type == "m") Mobs[MobStart++] = (NLS::Mob*)r;
	}
}

void NLS::Life::Init() {
	if (type == "m") {
		data = WZ["Mob"][id];
		name = (string)WZ["String"]["Mob"][id]["name"];
		speedMin = (double)abs((int)data["info"]["speed"]) + 10;
	}
	else if (type == "n") {
		data = WZ["Npc"][id];
		speedMin = 30;
		auto str =  WZ["String"]["Npc"][id];
		name = (string)str["name"];
		string scriptname = (string)data["info"]["script"]["0"]["script"];
		((Npc*)this)->function = (string)str["func"] + (scriptname.empty() ? "" : " (" + scriptname + ")");
		((Npc*)this)->functiontag.Set(((Npc*)this)->function, NameTag::Life);
	}

	down = false;
	up = false;
	notAPlayer = true;
	nametag.Set(name, NameTag::Life);
	if (data["info"]["link"]) {
		data = data[".."][data["info"]["link"]];
	}
	defaultState = data["info"]["flySpeed"] ? "fly" : "stand";
	ChangeState(defaultState);
}

void NLS::Life::ChangeState(const string &newState) {
	if (!data[newState]) {
		return;
	}
	if (newState == currentState) return;
	currentAnimation.Set(data[newState]);
	currentState = newState;
}

void NLS::Life::Draw() {
	Update();
	currentAnimation.Draw(x, y, data["info"]["noFlip"] ? 0 : f);
	if (!data["info"]["hideName"]) {
		nametag.Draw(x, y);
	}
}

void NLS::Life::Update() {
	if (data["move"]) {
		if (timeToNextAction-- <= 0) {
			switch (rand()%3) {
			case 0:
				left = true;
				right = false;
				timeToNextAction = (isNPC ? 0 : 100) + rand() % (type == "n" ? 90 : 100);
				break;
			case 1:
				left = false;
				right = true;
				timeToNextAction = (isNPC ? 0 : 100) + rand() % (type == "n" ? 90 : 100);
				break;
			case 2:
				left = false;
				right = false;
				timeToNextAction = rand() % (type == "n" ? 5000 : 1000);
				break;
			}
		}
	}
	Physics::Update();
	
	string state = defaultState;
	if (fh) {
		if (left^right) {
			state = "move";
		} 
		else {
			state = defaultState;
		}
	} 
	else if ((int)Map::node["info"]["swim"]) {
		state = "fly";
	}
	ChangeState(state);
	
	currentAnimation.Step();
}

void NLS::Npc::Draw() {
	NLS::Life::Draw();

	if (!function.empty()) {
		functiontag.Draw(x, y+15);
	}
	if (data["info"]["MapleTV"] && (int)data["info"]["MapleTV"] == 1) {
		int32_t mx = x + (int)data["info"]["MapleTVadX"];
		int32_t my = cy + (int)data["info"]["MapleTVadY"];

		NLS::Sprite sprite = WZ["UI"]["MapleTV"]["TVmedia"]["1"]["0"];
		my += sprite.data->height;

		if (!hasMapleTVAnim) {
			int32_t ad = rand() % 3;
			hasMapleTVAnim = true;
			mapleTVanim.Set(WZ["UI"]["MapleTV"]["TVmedia"][tostring(ad)]);
		}
		mapleTVanim.Step();

		mapleTVanim.Draw(mx, my, f);

		sprite = WZ["UI"]["MapleTV"]["TVbasic"]["0"];

		my = cy + (int)data["info"]["MapleTVmsgY"] + sprite.data->height;
		mx = x + (int16_t)(int)data["info"]["MapleTVmsgX"];
		
		sprite.Draw(mx, my, f);
	}
}

void NLS::Mob::Draw() {
	NLS::Life::Draw();
}