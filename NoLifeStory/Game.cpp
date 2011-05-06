///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

string curMap;
wz::node curMapNode;
bool Game::Running;
bool Game::DevPortals;
Game::RenderMode Game::Mode = Game::RenderMode::FADED;
Timer nlstime;
uint32_t last_delta;
uint32_t delta;
uint64_t tdelta;
uint32_t loadtime;
double fps;
double alpha;
bool alphaUP = false;
bool mindfuck = false;
sound music;
bool resort = false;
this_player *theplayer;

///////////////////////////////////////////////////////////////
// The primary stuff
///////////////////////////////////////////////////////////////
bool Game::init(string* argv, int argc) {
	Mode = Game::RenderMode::FADED;
	string map = "login";
	string path = ".";
	bool guildNameSet = false;
	string name = "", guild = "";
	for (auto i = 0; i < argc; i++) {
		if (argv[i] == "-map") {
			map = argv[i+1];
			i++;
		} else if (argv[i] == "-path") {
			path = argv[i+1];
			i++;
		} else if (argv[i] == "-name") {
			name = argv[i+1];
			i++;
		} else if (argv[i] == "-guild") {
			guild = argv[i+1];
			guildNameSet = true;
			i++;
		} else {

		}
	}
	if (path.find_last_of("\\")+1 == path.length()) {
		path.erase(path.find_last_of("\\")+1);
	}
	cout << "loading from " << path << endl;
	if (file_exists(path+"/Base.wz")) {
		cout << "Loading modern wz files" << endl;
		wz::init(path);
		wz::load("Base");
		wz::load("Character");
		wz::load("Effect");
		wz::load("Etc");
		wz::load("Item");
		wz::load("List");
		wz::load("Map");
		wz::load("Mob");
		wz::load("Morph");
		wz::load("Npc");
		wz::load("Quest");
		wz::load("Reactor");
		wz::load("Skill");
		wz::load("Sound");
		wz::load("String");
		wz::load("TamingMob");
		wz::load("UI");
	}
	else if (file_exists(path + "/Data.wz")) {
		cout << "Loading beta wz files" << endl;
		wz::init(path);
		wz::load("Data");
	}
	else {
		cout << "Nothing to load!" << endl;
		cin.get();
		exit(3);
	}
	init_graphics();
	Mix_Init(0xf);
	TTF_Init();
	Mouse::init();
	cout << "Initialization completed!" << endl;
	Map::Load(map, "");
	Map::Load();
	DevPortals = false;
	Running = true;
	fps = 100;
	tdelta = 0;
	alpha = 1;
	nlstime.start();
	last_delta = GET_DELTA;
	return true;
}

bool Game::loop() {
	Input::Handle();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	//Wheeeeeeeee
	if (mindfuck) {
		glMatrixMode(GL_PROJECTION);
		if (random(1) > 0.98) {
			glLoadIdentity();
			glOrtho(0, 800, 600, 0, -1, 1);
		}
		if (random(1) > 0.95) {
			glRotated(random(360), 0, 0, 1);
		}
		if (random(1) > 0.95) {
			glTranslated(random(100), random(100), 0);
		}
		glMatrixMode(GL_MODELVIEW);
	}
	glLoadIdentity();
	view.step();
	//Sorting objects
	if (resort) {
		sort(objects.begin(), objects.end(), [] (object* a, object* b) -> bool {
			for(auto i = 0; i < maxDepth; i++) {
				if (a->z[i] < b->z[i]) {
					return true;
				}
				if (a->z[i] > b->z[i]) {
					return false;
				}
			}
			return a > b;
		});
		resort = false;
	}
	//Drawing objects
	for (auto i = objects.begin(); i!= objects.end(); i++) {
		(*i)->draw();
	}
	glBindTexture(GL_TEXTURE_2D, NULL);
#ifdef _DEBUG
	for (auto i = ladders.begin(); i != ladders.end(); i++) {
		(*i)->draw();
	}
	for (auto i = footholds.begin(); i != footholds.end(); i++) {
		(*i)->draw();
	}
#endif

	if (Map::currentmap == "login") {

		Sprite sign = (Sprite)wz::top["UI"]["Login"]["Title"]["signboard"];
		sign.Draw(22, 17);
		int x = -251;
		int y = -860;
		Sprite btworld_empty = (Sprite)wz::top["UI"]["Login"]["WorldSelect"]["BtWorld"]["e"]["normal"]["0"];
		for (int i = 0; i < 5; i++ ) { // Rows
			for (int j = 0; j < 6; j++ ) {
				int8_t id = j + (i * 6);
				World *world = Worlds::GetWorld(id);
				if (world != nullptr) {
					world->img.Draw(-250 + (j * (world->img.width + 15)), -860 + (i * (world->img.height + 2)), true);
				}
				else {
					btworld_empty.Draw(-250 + (j * (btworld_empty.width + 15)), -860 + (i * (btworld_empty.height + 2)), true);
				}
			}
		}
		/*
		Sprite ID = (Sprite)wz::top["UI"]["Login"]["Title"]["ID"];
		ID.Draw(-100, -51, true);
		Sprite PW = (Sprite)wz::top["UI"]["Login"]["Title"]["PW"];
		PW.Draw(-100, -26, true);
		Sprite loginbtn = (Sprite)wz::top["UI"]["Login"]["Title"]["BtLogin"]["normal"]["0"];
		loginbtn.Draw(65, -51, true);
		*/
		Sprite frame = (Sprite)wz::top["UI"]["Login"]["Common"]["frame"];
		frame.Draw(frame.originx, frame.originy, false);
		Sprite guide = (Sprite)wz::top["Map"]["Obj"]["login"]["Guide"]["world"]["0"]["0"];
		guide.Draw(guide.width/2, guide.height/2, false);
	}
	else {
		Sprite frame = (Sprite)wz::top["UI"]["StatusBar"]["base"]["backgrnd"];
		frame.Draw(0, 600 - frame.height, false);
		frame = (Sprite)wz::top["UI"]["StatusBar"]["base"]["backgrnd2"];
		frame.Draw(0, 600 - frame.height, false);

	}

	Mouse::draw();

	DrawText("fps: " + tostring((int)fps), 0, 0, 12);
	DrawText("Character: x: " + tostring((int)view.tx+400) + " | y: " + tostring((int)view.ty+350) + " | Mouse: x: " + tostring(Mouse::x) + ", y: " + tostring(Mouse::y) + " | View vals: " + tostring(view.x) + ", " + tostring(view.y) + " " + tostring(view.vx) + ", " + tostring(view.vy), 0, 16, 12);
	DrawText("Mouse map: x: " + tostring(Mouse::x + view.x) + " | y: " + tostring(Mouse::y + view.y), 0, 32, 12);
	DrawText("Map ID: " + Map::currentmap, 0, 48, 12);
	// DrawableText test...
	DrawText("Life: " + tostring(lifes.size()) + ", (NPCs: " + tostring(npcs.size()) + " | Mobs: " + tostring(mobs.size()) + ")", 0, 64, 12);

	//Time stuff
	uint32_t temp = GET_DELTA;
	delta = temp - last_delta;
	delta = min((double)delta, 100.0);
	tdelta += delta;
	last_delta = temp;
	fps = (1000/max((double)delta, 1.0)+fps*9)/10;
	if (loadtime) {
		cout << "Loading time was " << int(GET_DELTA-loadtime) << "ms" << endl;
		loadtime = 0;
	}
	if (Map::nextmap != "" && Mode != RenderMode::FADED) {
		Mode = RenderMode::FADEIN;
	}
	switch (Mode) {
	case RenderMode::FADEIN: 
		if (alpha >= 1) {
			Mode = RenderMode::FADED;
			alpha = 1;
		} else {
			alpha += double(delta)/500;
		}
		break;
	case RenderMode::FADEOUT: 
		if (alpha <= 0) {
			Mode = RenderMode::NORMAL;
			alpha = 0;
#ifdef ONLINE
			if (Map::currentmap == "login") {
				string username, password;
				cout << "Login!" << endl << "Username: ";
				cin >> username;
				cout << "Password: ";
				cin >> password;

				PacketWriter pw;
				pw.Write<header_t>(0x01);
				pw.WriteString(username);
				pw.WriteString(password);
				ns->SendPacket(pw);
			}
#endif
		} else {
			alpha -= double(delta)/500;
		}
		break;
	case RenderMode::FADED:
		if (Map::nextmap != "") {
			Map::Load();
		} else {
			Game::Mode = RenderMode::FADEOUT;
		}
		break;
	}
	if (alpha > 0) {
		glLoadIdentity();
		glColor4d(0, 0, 0, alpha);
		glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(800, 0);
		glVertex2i(800, 600);
		glVertex2i(0, 600);
		glEnd();
	}
	glFlush();
	SDL_GL_SwapBuffers();

	return Running;
}

void Game::unload() {
	Mix_Quit();
	SDL_Quit();
}