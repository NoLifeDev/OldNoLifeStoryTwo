////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

vector <NLS::Portal*> NLS::Portal::Portals;
bool loaded = false;
NLS::Sprite sprites[15];

void NLS::Portal::Load(Node n) {
	if (!loaded) {
		Node sn =  WZ::Top["Map"]["MapHelper"]["portal"]["editor"];
		sprites[0] = sn["sp"];
		sprites[1] = sn["pi"];
		sprites[2] = sn["pv"];
		sprites[3] = sn["pc"];
		sprites[4] = sn["pg"];
		sprites[5] = sn["pgi"];
		sprites[6] = sn["tp"];
		sprites[7] = sn["ps"];
		sprites[8] = sn["psi"];
		sprites[9] = sn["pcs"];
		sprites[10] = sn["ph"];
		sprites[11] = sn["psh"];
		sprites[12] = sn["pcj"];
		sprites[13] = sn["pci"];
		sprites[14] = sn["pcig"];
		loaded = true;
	}
	for (auto it = Portals.begin(); it != Portals.end(); it++) {
		delete *it;
	}
	Portals.clear();
	n = n["portal"];
	for (auto it = n.Begin(); it != n.End(); it++) {
		Node pn = it->second;
		Portal* p = new Portal;
		p->x = pn["x"];
		p->y = pn["y"];
		p->pt = pn["pt"];
		p->pn = pn["pn"];
		p->tm = pn["tm"];
		p->tn = pn["tn"];
		p->script = pn["script"];
		p->hi = pn["horizontalImpact"];
		p->vi = pn["verticalImpact"];
		p->onlyonce = pn["onlyOnce"];
		p->hidetooltip = pn["hideTooltip"];
		p->delay = pn["delay"];
		Portals.push_back(p);
	}
}

void NLS::Portal::Draw() {
	//TODO: Animated portal types from game, rather than editor
	sprites[pt].Draw(x, y);
}