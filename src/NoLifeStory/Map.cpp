////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Node NLS::Map::node;
string NLS::Map::nextmap;
string NLS::Map::curmap;
string NLS::Map::nextportal;
int8_t NLS::Map::nextportalID = -1;
vector<NLS::Back*> NLS::Map::Backgrounds;
NLS::Map::Layer NLS::Map::Layers[8];
vector<NLS::Back*> NLS::Map::Foregrounds;
map<uint32_t, NLS::Player*> NLS::Map::Players;
NLS::Sound NLS::Map::bgmusic;
float NLS::Map::fade;
bool NLS::Map::Login;
//NLS::Text NLS::Map::scrollingHeader;

void NLS::Map::Load(const string& id, const string& portal) {
	nextmap = id;
	nextportal = portal;
}

void NLS::Map::Load() {
	auto teleport = [&](string portal, bool change) {
		if (portal.empty() && nextportalID == -1) {
			if (change) {
				portal = "sp";
			} else {
				return;
			}
		}
		vector <Portal*> possible;
		for_each(Portal::begin(), Portal::end(), [&](Portal* p){
			if (nextportalID == p->id or portal == p->pn) {
				possible.push_back(p);
			}
		});
		if (possible.size() == 0) {
			if (Portal::All.size() > 0) {
				// Insert the first one
				possible.insert(possible.end(), Portal::begin(), Portal::end());
			}
			else {
				// Oh god.
				cerr << "Could not determine a spawnplace. Map " << nextmap << endl;
				throw(273);
			}
		}

		int r = rand()%possible.size();
		ThisPlayer->Reset(possible[r]->x, possible[r]->y-16);
		if (change) {
			View::vx = ThisPlayer->x-View::width/2;
			View::vy = ThisPlayer->y-View::height/2;
		}
	};
	Node mn;
	if (nextmap == "MapLogin" || nextmap == "MapLogin2") {
		mn = WZ["UI"][nextmap];
		Login = true;
		Network::Online = true;
	} else {
		pad(nextmap, '0', 9);
		char zone = nextmap[0];
		mn = WZ["Map"]["Map"][string("Map")+zone][nextmap];
		Login = false;
	}
	if (curmap == nextmap) {
		cerr << "Map " << nextmap << " is already loaded" << endl;
		teleport(nextportal, false);
		nextmap = "";
		nextportal = "";
		return;
	}
	if (!mn) {
		if (nextmap != "999999999") {
			cerr << "Unable to locate map " << nextmap << endl;
			MainChat << Text::Color(255, 0, 0) << "[WARN] Map not found!" << cendl;
		}
		teleport(nextportal, false);
		nextmap = "";
		nextportal = "";
		return;
	}
	node = mn;
	if (node["info"]["link"]) {
		nextmap = node["info"]["link"];
		cout << "Following link to map " << nextmap << endl;
		Load();
		return;
	}
	if (!curmap.empty() and !Profiling) {
		glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
		glBlendFunc(GL_ONE, GL_ONE);
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor4ub(4, 4, 4, 0);
		glLoadIdentity();
		for (int i = 0; i < 128; ++i) {
			glBegin(GL_QUADS);
			glVertex2i(0, 0);
			glVertex2i(View::width, 0);
			glVertex2i(View::width, View::height);
			glVertex2i(0, View::height);
			glEnd();
			window->Display();
		}
		glColor4f(1, 1, 1, 1);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);
	}
	fade = 1;
	Time::Reset();
	curmap = nextmap;
	cout << "Loading map " << nextmap << endl;
	if (!Mindfuck) {
		string bgm = node["info"]["bgm"];
		vector<string> p = split(bgm, '/');
		if (p.size() == 2) {
			bgmusic = WZ["Sound"][p[0]][p[1]];
			bgmusic.Play(true);
		}
	}

	for (uint8_t i = 0; i < 8; ++i) {
		Layers[i].Tiles.clear();
		Layers[i].Objs.clear();
	}
	Backgrounds.clear();
	Foregrounds.clear();
	for_each(Players.begin(), Players.end(), [](pair<uint32_t, Player*> p) {delete p.second;});
	Players.clear();
	Sprite::Unload();

	Foothold::Load(node);
	Tile::Load(node);
	Obj::Load(node);
	Back::Load(node);
	Portal::Load(node);
	Reactor::Load(node);
	LadderRope::Load(node);
	Life::Load();
	View::tx = 0;
	View::ty = 0;
	if (node["info"]["VRLeft"]) {
		View::xmin = node["info"]["VRLeft"];
		View::xmax = node["info"]["VRRight"];
		View::ymin = node["info"]["VRTop"];
		View::ymax = node["info"]["VRBottom"];
	} else {
		View::xmin = 1000000;
		View::xmax = -1000000;
		View::ymin = 1000000;
		View::ymax = -1000000;
		for_each(Foothold::begin(), Foothold::end(), [&](Foothold* fh){
			View::xmin = min(min((double)View::xmin, fh->x1), fh->x2);
			View::ymin = min(min((double)View::ymin, fh->y1), fh->y2);
			View::xmax = max(max((double)View::xmax, fh->x1), fh->x2);
			View::ymax = max(max((double)View::ymax, fh->y1), fh->y2);
		});
		View::ymax += 128;
		View::ymin -= View::height;
	}
	teleport(nextportal, true);
	nextmap = "";
	nextportal = "";
	nextportalID = -1;
	//scrollingHeader.Set(Text::Color(255,255,0)+u32("TEST"), 14);
}

void NLS::Map::Draw() {
	for (uint32_t i = 0; i < Backgrounds.size(); ++i) {
		Backgrounds[i]->Draw();
	}
	for (uint32_t i = 0; i < Reactor::Reactors.size(); ++i) {
		Reactor::Reactors[i]->Draw();
	}
	for (uint8_t i = 0; i < 8; i++) {
		Layers[i].Draw();
		if (!Login and ThisPlayer->layer == i) {
			ThisPlayer->Draw();
		}
	}
	for (uint32_t i = 0; i < Life::Mobs.size(); ++i) {
		Life::Mobs[i]->Draw();
	}
	for (uint32_t i = 0; i < Life::Npcs.size(); ++i) {
		Life::Npcs[i]->Draw();
	}

	for_each(Players.begin(), Players.end(), [](pair<uint32_t, Player*> p){p.second->Draw();});

	for_each(Portal::begin(), Portal::end(), [](Portal* p){p->Draw();});

	for (uint32_t i = 0; i < Foregrounds.size(); ++i) {
		Foregrounds[i]->Draw();
	}
	DrawClock();
}

void NLS::Map::Layer::Draw() {
	for (auto it = Objs.begin(); it != Objs.end(); ++it) {
		(*it)->Draw();
	}
	for (auto it = Tiles.begin(); it != Tiles.end(); ++it) {
		(*it)->Draw();
	}
}

void NLS::Map::DrawClock() {
	if (!node["clock"]) return;
	int32_t x = node["clock"]["x"], y = node["clock"]["y"];
	NLS::Node clockImgs = WZ["Map"]["Obj"]["etc"]["clock"]["fontTime"];

	y += 81;
	x += 12;

	time_t rawtime = time(0);
	tm *timeinfo = localtime(&rawtime);
	uint8_t digit_1 = timeinfo->tm_hour / 10;
	uint8_t digit_2 = timeinfo->tm_hour % 10;
	uint8_t digit_3 = timeinfo->tm_min / 10;
	uint8_t digit_4 = timeinfo->tm_min % 10;
	
	string ampm = timeinfo->tm_hour >= 12 ? "pm" : "am";

	Sprite sprite_ampm = clockImgs[ampm];
	sprite_ampm.Draw(x, y);

	x += sprite_ampm.data->width + 10;

	Sprite digit = clockImgs[tostring(digit_1)];
	digit.Draw(x, y);
	x += digit.data->width + 5;

	digit = clockImgs[tostring(digit_2)];
	digit.Draw(x, y);
	x += digit.data->width + 5;

	digit = clockImgs["comma"];
	digit.Draw(x, y);
	x += digit.data->width + 5;

	digit = clockImgs[tostring(digit_3)];
	digit.Draw(x, y);
	x += digit.data->width + 5;

	digit = clockImgs[tostring(digit_4)];
	digit.Draw(x, y);
}

NLS::Player * NLS::Map::GetPlayer(uint32_t playerid) {
	return Players.find(playerid) != Players.end() ? Players[playerid] : nullptr;
}