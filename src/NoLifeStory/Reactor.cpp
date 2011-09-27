////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

vector <NLS::Reactor*> NLS::Reactor::Reactors;

void NLS::Reactor::Load(Node n) {
	for (auto it = Reactors.begin(); it != Reactors.end(); it++) {
		delete *it;
	}
	Reactors.clear();
	n = n["reactor"];
	if (!n) {
		return;
	}
	for (auto it = n.Begin(); it != n.End(); it++) {
		Node rn = it->second;
		Reactor* r = new Reactor;
		r->x = rn["x"];
		r->y = rn["y"];
		r->f = (int)rn["f"];
		r->time = rn["reactorTime"];
		r->name = rn["name"];
		r->id = rn["id"];
		r->data = WZ["Reactor"][r->id];
		Reactors.push_back(r);
		C("INFO") << "Reactor " << r->id << endl;
		C("") << "frontTile " << (int)r->data["frontTile"] << endl;
		C("") << "level " << (int)r->data["level"] << endl;
		C("") << "resetTime " << (int)r->data["resetTime"] << endl;
		C("") << "viewName " << (string)r->data["viewName"] << endl;
	}
}

void NLS::Reactor::Draw() {
	Sprite s = data["0"]["0"];
	s.Draw(x, y, f);
}