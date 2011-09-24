////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Node NLS::Map::node;
string NLS::Map::nextmap;
string NLS::Map::curmap;
string NLS::Map::nextportal;
vector<NLS::Back*> NLS::Map::Backgrounds;
NLS::Map::Layer NLS::Map::Layers[8];
vector<NLS::Back*> NLS::Map::Foregrounds;
NLS::Sound NLS::Map::bgmusic;

void NLS::Map::Load(const string& id, const string& portal) {
	nextmap = id;
	nextportal = portal;
}

void NLS::Map::Load() {
	if (curmap == nextmap) {
		C("ERROR") << "The specified map is already loaded" << endl;
		nextmap = "";
		return;
	}
	if (nextmap == "MapLogin") {
		node = WZ::Top["UI"]["MapLogin"];
		//throw(273);
	} else {
		if (nextmap.size() < 9) {
			nextmap.insert(0, 9-nextmap.size(), '0');
		}
		char zone = nextmap[0];
		node = WZ::Top["Map"]["Map"][string("Map")+zone][nextmap];
	}
	if (!node) {
		C("ERROR") << "Unable to locate map " << nextmap << endl;
		nextmap = "";
		nextportal = "";
		return;
	}
	Time.Reset();
	curmap = nextmap;
	C("INFO") << "Loading map " << nextmap << endl;
	string bgm = node["info"]["bgm"];
	auto p = bgm.find('/');
	bgmusic = WZ::Top["Sound"][bgm.substr(0, p)][bgm.substr(p+1)];
	bgmusic.Play(true);
	for (uint8_t i = 0; i < 8; i++) {
		Layers[i].Tiles.clear();
		Layers[i].Objs.clear();
	}
	Backgrounds.clear();
	Foregrounds.clear();
	Sprite::Unload();
	Foothold::Load(node);
	Tile::Load(node);
	Obj::Load(node);
	Back::Load(node);
	Portal::Load(node);
	Reactor::Load(node);
	View.tx = 0;
	View.ty = 0;
	if (node["info"]["VRLeft"]) {
		View.xmin = node["info"]["VRLeft"];
		View.xmax = node["info"]["VRRight"];
		View.ymin = node["info"]["VRTop"];
		View.ymax = node["info"]["VRBottom"];
	} else {
		View.xmin = 1000000;
		View.xmax = -1000000;
		View.ymin = 1000000;
		View.ymax = -1000000;
		for (auto it = footholds.begin(); it != footholds.end(); it++) {
			View.xmin = min(min(View.xmin, (*it)->x1), (*it)->x2);
			View.ymin = min(min(View.ymin, (*it)->y1), (*it)->y2);
			View.xmax = max(max(View.xmax, (*it)->x1), (*it)->x2);
			View.ymax = max(max(View.ymax, (*it)->y1), (*it)->y2);
		}
		View.ymax += 128;
		View.ymin -= View.height;
	}
	nextmap = "";
	nextportal = "";
}

void NLS::Map::Draw() {
	for (uint32_t i = 0; i < Backgrounds.size(); i++) {
		Backgrounds[i]->Draw();
	}
	for (uint8_t i = 0; i < 8; i++) {
		Layers[i].Draw();
	}
	for (uint32_t i = 0; i < Portal::Portals.size(); i++) {
		Portal::Portals[i]->Draw();
	}
	for (uint32_t i = 0; i < Foregrounds.size(); i++) {
		Foregrounds[i]->Draw();
	}
}

void NLS::Map::Layer::Draw() {
	for (auto it = Objs.begin(); it != Objs.end(); it++) {
		(*it)->Draw();
	}
	for (auto it = Tiles.begin(); it != Tiles.end(); it++) {
		(*it)->Draw();
	}
}