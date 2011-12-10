////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set<NLS::Portal*> NLS::Portal::All;
bool loaded = false;
NLS::Sprite sprites[15];
NLS::AniSprite pvsprite;
NLS::AniSprite phsprite;
string portalNames[15] = {"sp", "pi", "pv", "pc", "pg", "pgi", "tp", "ps", "psi", "pcs", "ph", "psh", "pcj", "pci", "pcig"};

void NLS::Portal::Load(Node n) {
	if (!loaded) {
		Node sn =  WZ["Map"]["MapHelper"]["portal"]["editor"];
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
		pvsprite.Set(WZ["Map"]["MapHelper"]["portal"]["game"]["pv"]);
		loaded = true;
	}
	for_each(begin(), end(), [](Portal* p){delete p;});
	All.clear();
	n = n["portal"];
	for (auto it = n.begin(); it != n.end(); it++) {
		Node pn = it->second;
		Portal* p = new Portal;
		p->id = toint(it->first);
		p->x = pn["x"];
		p->y = pn["y"];
		p->pt = pn["pt"];
		p->tm = (string) pn["tm"];
		p->pn = (string) pn["pn"];
		p->tn = (string) pn["tn"];
		p->script = (string) pn["script"];
		p->hi = pn["horizontalImpact"];
		p->vi = pn["verticalImpact"];
		if (!p->hi and p->pt==12) p->hi = 300;
		if (!p->vi and p->pt==12) p->vi = 2200;
		p->onlyonce = pn["onlyOnce"];
		p->hidetooltip = pn["hideTooltip"];
		p->delay = pn["delay"];
		p->derp.Set(portalNames[p->pt]+(p->script.empty()?"":": "+p->script), NameTag::Normal);
		p->phState = Portal::Nothing;
		All.insert(p);
	}
}

void NLS::Portal::Update() {
	pvsprite.Step();
}

void NLS::Portal::Draw() {
	int32_t h = ThisPlayer->y - y;
	switch (pt) {
	case 2:
		pvsprite.Draw(x, y);
		break;
	case 10:
		sprites[pt].Draw(x, y);
		if (abs(ThisPlayer->x - x) < 60 and h > -90 and h < 10) {
			if (phState == Portal::Nothing || phState == Portal::Exit) {
				phsprite.Set(WZ["Map"]["MapHelper"]["portal"]["game"]["ph"]["default"]["portalStart"]);
				phState = Portal::Start;
				phsprite.repeat = false;
			} else if (phsprite.done) {
				if (phState == Portal::Start) {
					phsprite.Set(WZ["Map"]["MapHelper"]["portal"]["game"]["ph"]["default"]["portalContinue"]);
					phState = Portal::Continue;
					phsprite.repeat = true;
				}
			}
			phsprite.Draw(x, y);
			phsprite.Step();
		} else if (phState != Portal::Nothing) {
			if (phState != Portal::Exit) {
				phsprite.Set(WZ["Map"]["MapHelper"]["portal"]["game"]["ph"]["default"]["portalExit"]);
				phState = Portal::Exit;
				phsprite.repeat = false;
			}
			if (!phsprite.done) {
				phsprite.Draw(x, y);
				phsprite.Step();
			} else if (phState == Portal::Exit) {
				phState = Portal::Nothing;
			}
		}
		break;
	default:
		sprites[pt].Draw(x, y);
	}
	derp.Draw(x, y);
}
