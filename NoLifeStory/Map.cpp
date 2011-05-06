///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

string Map::nextmap = "";
string Map::nextportal = "";
string Map::currentmap = "";
wz::node Map::node;
int Map::currentLoginStep = 0;

void Map::Load(string id, string portal) {
	nextmap = id;
	nextportal = portal;
}

void Map::Load() {
	//Making sure the screen is black
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapBuffers();
	wz::node mapNode;
	char mapZone;
	if (nextmap == "login") {
		if (wz::top["UI"]["MapLogin1"]) {
			mapNode = wz::top["UI"]["MapLogin1"];
		} else {
			mapNode = wz::top["UI"]["MapLogin"];
		}
		mapZone = 'x';
	} else {
		while(nextmap.size()<9) {
			nextmap = "0"+nextmap;
		}
		mapZone = nextmap[0];
		mapNode = wz::top["Map"]["Map"][string("Map")+mapZone][nextmap];
	}
	if (!mapNode) {
		cout << "Cannot load map " << nextmap << " in zone " << mapZone << "; It doesn't exist!" << endl;
		nextmap = "";
		nextportal = "";
		return;
	}

	//Now we can begin!
	currentmap = nextmap;
	node = mapNode;
	loadtime = GET_DELTA;
	cout << "Loading map " << nextmap << " in zone " << mapZone << endl;

	//Clearing Garbage
	unload_sprites();
	while (!objects.empty()) {
		auto it = objects.begin();
		delete *it;
	}
	objects.clear();
	portals.clear();
	footholds.clear();
	ladders.clear();
	lifes.clear();
	npcs.clear();
	mobs.clear();

	string bgm = mapNode["info"]["bgm"];
	int pos = bgm.find_first_of("/");
	music = wz::top["Sound"][bgm.substr(0, pos)][bgm.substr(pos+1)];
	//music.play();

	cout << "Loading footholds..." << endl;
	LoadFoothold();
	cout << "Loading ladders..." << endl;
	LoadLadder();
	cout << "Loading tiles..." << endl;
	LoadTile();
	cout << "Loading portals..." << endl;
	LoadPortal();
	cout << "Loading objects..." << endl;
	LoadObj();
	cout << "Loading backgrounds..." << endl;
	LoadBack();
	cout << "Loading life..." << endl;
	LoadLife();
	
	if (currentmap != "login") {
		// Re-assign the depth and such
		theplayer = new this_player();
		theplayer->z = depth::layer;
		theplayer->z = 8;
		theplayer->z = depth::player;
		theplayer->f = true;

		for(auto i = portals.begin(); i != portals.end(); i++) {
			auto other = *i;
			if (other->pt == 0) {
				theplayer->x = other->x;
				theplayer->y = other->y-32;
				break;
			}
		}
		if (nextportal != "") {
			for (auto i = portals.begin(); i != portals.end(); i++) {
				auto other = *i;
				if (other->pn == nextportal) {
					theplayer->x = other->x;
					theplayer->y = other->y-32;
					nextportal = "";
					break;
				}
			}
		}
		view.x = theplayer->x-400;
		view.y = theplayer->y-300;
		view.vx = theplayer->x-400;
		view.vy = theplayer->y-300;
		view.tx = theplayer->x-400;
		view.ty = theplayer->y-300;
		if (mapNode["info"]["VRLeft"]) {
			view.xmin = mapNode["info"]["VRLeft"];
			view.xmax = mapNode["info"]["VRRight"];
			view.ymin = mapNode["info"]["VRTop"];
			view.ymax = mapNode["info"]["VRBottom"];
		} else {
			GenerateMapDimensions();
		}
	} else {
		GenerateMapDimensions();
		view.ymin -= 4400;
		view.xmax -= 90;
		view.xmin -= 9;
		ChangeLoginStep(0);
	}
	nextmap = "";
	nextportal = "";
	resort = true;
	cout << "Loading sprites..." << endl;
}

void Map::LoadFoothold() {
	wz::node fhnode = node["foothold"];
	if (!fhnode) {
		return;
	}
	for (auto i = fhnode.begin(); i!=fhnode.end(); i++) {
		int fhdepth = toreal(i->first);
		for (auto j = i->second.begin(); j!=i->second.end(); j++) {
			int fhgroup = toreal(j->first);
			for (auto k = j->second.begin(); k!=j->second.end(); k++) {
				wz::node& fh = k->second;
				foothold* nfh = new foothold(fh["x1"], fh["y1"], fh["x2"], fh["y2"]);
				nfh->nextid = fh["next"];
				nfh->previd = fh["prev"];
				nfh->id = toreal(k->first);
				nfh->layer = fhdepth;
				nfh->group = fhgroup;
				nfh->force = fh["force"];
				nfh->forbid = fh["forbidFallDown"] ? true : false; // Sometimes not set; so we need to do a test ourselfs
			}
		}
	}
	for (auto i = footholds.begin(); i != footholds.end(); i++) {
		for (auto j = footholds.begin(); j != footholds.end(); j++) {
			if (*i == *j) {
				continue;
			}
			if ((*i)->nextid == (*j)->id) {
				(*i)->next = *j;
			}
			if ((*i)->previd == (*j)->id) {
				(*i)->prev = *j;
			}
		}
	}
}

void Map::LoadLadder() {
	wz::node lrnode = node["ladderRope"];
	if (!lrnode) {
		return;
	}
	for (auto i = lrnode.begin(); i!=lrnode.end(); i++) {
		int id = toreal(i->first);
		wz::node& lr = i->second;
		ladder* nlr = new ladder();
		nlr->x = lr["x"];
		nlr->y1 = lr["y1"];
		nlr->y2 = lr["y2"];
		nlr->l = lr["l"];
		nlr->page = lr["page"];
		nlr->uf = lr["uf"];
	}
}

void Map::LoadTile() {
	for(auto i=0;i<8;i++) {
		wz::node layernode = node[tostring(i)];
		string type = layernode["info"]["tS"];
		for(auto j=0; layernode["tile"][tostring(j)]; j++) {
			wz::node tilenode = layernode["tile"][tostring(j)];
			string u = tilenode["u"];
			string no = tostring((int)tilenode["no"]);
			wz::node tiledata = wz::top["Map"]["Tile"][type][u][no];
			tile* ntile = new tile;
			ntile->spr = tiledata;
			ntile->x = tilenode["x"];
			ntile->y = tilenode["y"];
			ntile->z = depth::layer;
			ntile->z = i;
			ntile->z = depth::tile;
			ntile->z = tiledata["z"];
		}
	}
}

void Map::LoadPortal() {
	wz::node layernode = node["portal"];
	for (auto i=0; layernode[tostring(i)]; i++) {
		wz::node portalnode = layernode[tostring(i)];
		portal* nportal = new portal;
		wz::node portalimage;
		nportal->x = portalnode["x"];
		nportal->y = portalnode["y"];
		nportal->pt = portalnode["pt"];
		nportal->pn = string(portalnode["pn"]);
		nportal->tm = portalnode["tm"];
		nportal->tn = string(portalnode["tn"]);
		nportal->script = string(portalnode["script"]);
		nportal->hi = portalnode["horizontalImpact"];
		nportal->vi = portalnode["verticalImpact"];
		nportal->onlyOnce = portalnode["onlyOnce"];
		nportal->hideTooltip = portalnode["hideTooltip"];
		nportal->uDelay = portalnode["delay"];
		nportal->z = depth::layer;
		nportal->z = 8;
		nportal->z = depth::portal;
	}
}

void Map::LoadObj() {
	for(auto i=0;i<8;i++) {
		wz::node layernode = node[tostring(i)];
		for(auto j=0; layernode["obj"][tostring(j)]; j++) {
			wz::node objnode = layernode["obj"][tostring(j)];
			string type1 = objnode["oS"];
			string type2 = objnode["l0"];
			string type3 = objnode["l1"];
			string type4 = objnode["l2"];
			wz::node objdata = wz::top["Map"]["Obj"][type1][type2][type3][type4]["0"];
			obj* nobj = new obj;
			nobj->spr = objdata;
			nobj->x = objnode["x"];
			nobj->y = objnode["y"];
			nobj->flow = objnode["flow"];
			nobj->rx = objnode["rx"];
			nobj->ry = objnode["ry"];
			nobj->f = (int)objnode["f"];
			nobj->repeat = (int)objdata["repeat"];
			nobj->movetype = objdata["moveType"];
			nobj->movew = objdata["moveW"];
			nobj->moveh = objdata["moveH"];
			nobj->movep = objdata["moveP"];
			nobj->mover = objdata["moveR"];
			nobj->z = depth::layer;
			nobj->z = i;
			nobj->z = depth::obj;
			nobj->z = objnode["z"];
			nobj->z = objdata["z"];
			nobj->data = wz::top["Map"]["Obj"][type1][type2][type3][type4];
		}
	}
}

void Map::LoadBack() {
	wz::node layernode = node["back"];
	for(auto j=0; layernode[tostring(j)]; j++) {
		wz::node backnode = layernode[tostring(j)];
		string type1 = backnode["bS"];
		string type2 = tostring((int)backnode["no"]);
		if (type1 == "") {
			continue;
		}
		back* nback = new back;
		nback->ani = (int)backnode["ani"];
		nback->x = backnode["x"];
		nback->y = backnode["y"];
		nback->f = (int)backnode["f"];
		nback->cx = backnode["cx"];
		nback->cy = backnode["cy"];
		nback->rx = backnode["rx"];
		nback->ry = backnode["ry"];
		nback->type = backnode["type"];
		if ((int)backnode["front"] == 1) {
			nback->z = depth::front;
		} else {
			nback->z = depth::back;
		}
		nback->z = j;
		wz::node backdata;
		if (nback->ani) {
			backdata = wz::top["Map"]["Back"][type1]["ani"][type2];
			nback->data = backdata;
			nback->movetype = backdata["0"]["moveType"];
			nback->movew = backdata["0"]["moveW"];
			nback->moveh = backdata["0"]["moveH"];
			nback->movep = backdata["0"]["moveP"];
			nback->mover = backdata["0"]["moveR"];
		} else {
			backdata = wz::top["Map"]["Back"][type1]["back"][type2];
			nback->spr = backdata;
			if (nback->cx == 0) {
				nback->cx = backdata["width"];
			}
			if (nback->cy == 0) {
				nback->cy = backdata["height"];
			}
			nback->movetype = backdata["moveType"];
			nback->movew = backdata["moveW"];
			nback->moveh = backdata["moveH"];
			nback->movep = backdata["moveP"];
			nback->mover = backdata["moveR"];
		}
	}
}

void Map::LoadLife() {
	wz::node lifenode = node["life"];
	for (auto i = 0; lifenode[tostring(i)]; i++) {
		wz::node Life = lifenode[tostring(i)];
		string lifetype = (string)Life["type"];
		if (lifetype == "n") {
			npc* nlife = new npc;
			nlife->id = (string)Life["id"];
			int id = atoi(nlife->id.c_str());
			while(nlife->id.size()<7) {
				nlife->id = "0"+nlife->id;
			}
			wz::node img = wz::top["Npc"][(string)Life["id"]];
			if (img["info"]["link"]) {
				img = wz::top["Npc"][(string)img["info"]["link"]];
			}
			nlife->img = img;
			nlife->x = Life["x"];
			nlife->y = Life["cy"];
			nlife->rx0 = Life["rx0"];
			nlife->rx1 = Life["rx1"];
			nlife->f = (bool)(int)Life["f"];
			nlife->mobtime = Life["mobtime"];
			nlife->state = "stand";
			nlife->hidename = (int)img["info"]["hideName"];
			nlife->name = (string)wz::top["String"]["Npc"][tostring(id)]["name"];
			nlife->z = depth::layer;
			nlife->z = 8;
			nlife->z = depth::life;
		} else if (lifetype == "m") {
			wz::node img = wz::top["Mob"][(string)Life["id"]];
			if (img["info"]["link"]) {
				img = wz::top["Mob"][(string)img["info"]["link"]];
			}
			mob* nlife = new mob;
			nlife->img = img;
			nlife->id = (string)Life["id"];
			int id = atoi(nlife->id.c_str());
			while(nlife->id.size()<7) {
				nlife->id = "0"+nlife->id;
			}
			nlife->x = Life["x"];
			nlife->y = Life["cy"];
			nlife->f = (bool)(int)Life["f"];
			nlife->rx0 = Life["rx0"];
			nlife->rx1 = Life["rx1"];
			nlife->mobtime = Life["mobtime"];
			nlife->init();
		}
	}
}

void Map::ChangeLoginStep(int8_t step) {
	view.y = view.ty = view.vy = -8 - 300 - (600 * step);
	currentLoginStep = step;
}

void Map::GenerateMapDimensions() {
	view.xmin = 1000000;
	view.xmax = -1000000;
	view.ymin = 1000000;
	view.ymax = -1000000;

	for (auto i = footholds.begin(); i != footholds.end(); i++) {
		view.xmin = min(min(view.xmin, (*i)->x1), (*i)->x2);
		view.ymin = min(min(view.ymin, (*i)->y1), (*i)->y2);
		view.xmax = max(max(view.xmax, (*i)->x1), (*i)->x2);
		view.ymax = max(max(view.ymax, (*i)->y1), (*i)->y2);
	}

	if (view.xmax-view.xmin > 800) {
		view.xmin -= 10;
		view.xmax += 10;
	}

	view.ymax += 110;
	view.ymin = min(view.ymax-600, view.ymin-360);	
}