////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

set <NLS::Tile*> NLS::Tile::Tiles;

void NLS::Tile::Load(Node n) {
	for (auto it = Tiles.begin(); it != Tiles.end(); it++) {
		delete *it;
	}
	Tiles.clear();
	for (uint8_t i = 0; i < 8; i++) {
		Node ln  = n[i];
		string type = ln["info"]["tS"];
		if (!ln["tile"]) {
			continue;
		}
		for (auto it = ln["tile"].Begin(); it != ln["tile"].End(); it++) {
			Node tn = it->second;
			string u = tn["u"];
			string no = tn["no"];
			Node td = WZ::Top["Map"]["Tile"][type][u][no];
			Tile *t = new Tile;
			t->spr = td;
			t->x = tn["x"];
			t->y = tn["y"];
			t->z = td["z"];
			Map::Layers[i].Tiles.push_back(t);
			Tiles.insert(t);
		}
		sort(Map::Layers[i].Tiles.begin(), Map::Layers[i].Tiles.end(), [](Tile* t1, Tile* t2){return t1->z < t2->z;});
	}
}

void NLS::Tile::Draw() {
	spr.Draw(x, y);
}