////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

vector <NLS::Life *> NLS::Life::Lifes;

void NLS::Life::Load() {
	for (auto it = Lifes.begin(); it != Lifes.end(); it++) {
		delete *it;
	}
	Lifes.clear();

	Node data = NLS::Map::node["life"];
	if (!data) return;
	
	for (auto it = data.begin(); it != data.end(); it++) {
		Node rn = it->second;
		Life* r = new Life;
		r->x = rn["x"];
		r->y = rn["y"];
		r->cx = rn["cx"];
		r->cy = rn["cy"];
		r->rx0 = rn["rx0"];
		r->rx1 = rn["ry1"];
		r->f = (int)rn["f"];
		r->time = rn["mobTime"];
		r->type = (string) rn["type"];
		r->id = (string) rn["id"];
		if (r->type == "n")			r->data = WZ["Npc"][r->id];
		else if (r->type == "m")	r->data = WZ["Mob"][r->id];
		else {
			cerr << "[WARN] Loading unknown 'life'! Map: " << NLS::Map::curmap << ", Life list ID: " << it->first << ", Type: " << r->type << endl;
			// Safe mode, Erwin style
			//  delete r;
			//  continue;
			// Rage mode, Peter style
			throw(273); // Goodbye cruel world.
		}
		if (r->data["info"]["link"]) {
			r->data = r->data[".."][r->data["info"]["link"]];
			// Linked mobs... common!
		}
		r->Init();
		Lifes.push_back(r);
	}
}

void NLS::Life::Init() {
	defaultState = data["info"]["flySpeed"] ? "fly" : "stand";
	ChangeState(defaultState);
}

void NLS::Life::ChangeState(const string &newState) {
	if (!data[newState]) throw(273);
	currentAnimation.Set(data[newState]);
	currentState = newState;
}

void NLS::Life::Draw() {
	Update();
	currentAnimation.Draw(x, cy, f);
}

void NLS::Life::Update() {
	currentAnimation.Step();
}