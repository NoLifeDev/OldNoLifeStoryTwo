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
float NLS::Map::fade;

NLS::ChatDialog *NLS::Map::dialog = nullptr;

void NLS::Map::Load(const string& id, const string& portal) {
	nextmap = id;
	nextportal = portal;
}

void NLS::Map::Load() {
	auto teleport = [&](string portal, bool change) {
		if (portal.empty()) {
			if (change) {
				portal = "sp";
			} else {
				return;
			}
		}
		vector <Portal*> possible;
		for (auto it = Portal::Portals.begin(); it != Portal::Portals.end(); it++) {
			Portal* p = *it;
			if (portal == p->pn) {
				possible.push_back(p);
			}
		}
		if (possible.empty()) {
			return;
		}
		int r = rand()%possible.size();
		ThisPlayer->Reset(possible[r]->x, possible[r]->y-16);
		if (change) {
			View::vx = ThisPlayer->x-View::width/2;
			View::vy = ThisPlayer->y-View::height/2;
		}
	};
	if (curmap == nextmap) {
		cerr << "The specified map is already loaded" << endl;
		teleport(nextportal, false);
		nextmap = "";
		nextportal = "";
		return;
	}
	if (nextmap == "MapLogin") {
		node = WZ["UI"]["MapLogin"];
		throw(273);//We don't deal with this shit yet
	} else {
		pad(nextmap, '0', 9);
		char zone = nextmap[0];
		node = WZ["Map"]["Map"][string("Map")+zone][nextmap];
	}
	if (!node) {
		cerr << "Unable to locate map " << nextmap << endl;
		MainChat << Text::Color(255, 0, 0) << "[WARN] Map not found!" << cendl;
		teleport(nextportal, false);
		nextmap = "";
		nextportal = "";
		return;
	}
	if (!curmap.empty()) {
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
		bgmusic = WZ["Sound"][p[0]][p[1]];
		bgmusic.Play(true);
	}
	for (uint8_t i = 0; i < 8; ++i) {
		Layers[i].Tiles.clear();
		Layers[i].Objs.clear();
	}
	Backgrounds.clear();
	Foregrounds.clear();

	// check if linked.
	if (node["info"]["link"]) {
		int32_t link = node["info"]["link"];
		node = node[".."][link];
	}

	if (dialog == nullptr) {
		dialog = new NLS::ChatDialog();
	}

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
	}
	for (uint32_t i = 0; i < Life::Mobs.size(); ++i) {
		Life::Mobs[i]->Draw();
	}
	for (uint32_t i = 0; i < Life::Npcs.size(); ++i) {
		Life::Npcs[i]->Draw();
	}
	ThisPlayer->Draw();
	for (uint32_t i = 0; i < Portal::Portals.size(); ++i) {
		Portal::Portals[i]->Draw();
	}
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