////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

vector <NLS::Mob *> NLS::Life::Mobs;
vector <NLS::Npc *> NLS::Life::Npcs;

void NLS::Life::Load() {
	for (auto it = Mobs.begin(); it != Mobs.end(); it++) {
		delete *it;
	}
	Mobs.clear();
	for (auto it = Npcs.begin(); it != Npcs.end(); it++) {
		delete *it;
	}
	Npcs.clear();

	Node data = Map::node["life"];
	if (!data) return;
	
	for (auto it = data.begin(); it != data.end(); it++) {
		Node rn = it->second;
		Life* r;
		string type = (string) rn["type"];
		if (type == "n")	{
			r = new Npc;
			r->id = (string)rn["id"];
			r->data = WZ["Npc"][r->id];
			auto str =  WZ["String"]["Npc"][r->id];
			r->name = (string)str["name"];
			((Npc*)r)->function = (string)str["func"];
			((Npc*)r)->functiontag.Set(((Npc*)r)->function);
			r->speedMin = 30;
		}
		else if (type == "m") {
			r = new Mob;
			r->id = (string)rn["id"];
			r->data = WZ["Mob"][r->id];
			r->name = (string)WZ["String"]["Mob"][r->id]["name"];
			r->speedMin = (double)abs((int)r->data["info"]["speed"]) + 10;
		}
		else {
			cerr << "[WARN] Loading unknown 'life'! Map: " << Map::curmap << ", Life list ID: " << it->first << ", Type: " << r->type << endl;
			// Safe mode, Erwin style
			//  delete r;
			//  continue;
			// Rage mode, Peter style
			throw(273); // Goodbye cruel world.
		}
		r->x = rn["x"];
		r->y = rn["y"];
		r->cx = rn["cx"];
		r->cy = rn["cy"];
		r->rx0 = rn["rx0"];
		r->rx1 = rn["ry1"];
		r->f = (int)rn["f"];
		r->time = rn["mobTime"];
		r->type = type;
		r->down = false;
		r->up = false;
		r->notAPlayer = true;
		r->nametag.Set(r->name);
		if (r->data["info"]["link"]) {
			r->data = r->data[".."][r->data["info"]["link"]];
			// Linked mobs... common!
		}
		r->Init();
		r->Reset(r->x, r->y);
		if (r->type == "n") Npcs.push_back((NLS::Npc*)r);
		else if (r->type == "m") Mobs.push_back((NLS::Mob*)r);
	}
}

void NLS::Life::Init() {
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
	currentAnimation.Draw(x, y, f);
	nametag.Draw(x, y);
}

void NLS::Life::Update() {
	if (data["move"]) {
		if (timeToNextAction-- <= 0) {
			switch (rand()%3) {
			case 0:
				left = true;
				right = false;
				timeToNextAction = rand() % (type == "n" ? 90 : 100);
				break;
			case 1:
				left = false;
				right = true;
				timeToNextAction = rand() % (type == "n" ? 90 : 100);
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
		
		sprite.Draw(mx, my, f);
	}
}

void NLS::Mob::Draw() {
	NLS::Life::Draw();
}