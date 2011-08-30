////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Node NLS::Map::node;
string NLS::Map::nextmap;
string NLS::Map::nextportal;

void NLS::Map::Load(string id, string portal) {
	nextmap = id;
	nextportal = portal;
}

void NLS::Map::Load() {
	char zone;
	nextmap.insert(0, 9-nextmap.size(), '0');
	zone = nextmap[0];
	node = WZ::Top["Map"]["Map"][string("Map")+zone][nextmap];
	string bgm = node["info"]["bgm"];
	cout << "INFO: Background music: " << bgm << endl;
}