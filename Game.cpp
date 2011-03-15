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
double last_delta;
double delta;
double tdelta;
double loadtime;
double fps;
double alpha;
bool alphaUP = false;
bool mindfuck = false;
sound music;
bool resort = false;
vector<string> mtl;
this_player *theplayer;

///////////////////////////////////////////////////////////////
// The primary stuff
///////////////////////////////////////////////////////////////
bool Game::init(string* argv, int argc) {
	Mode = Game::RenderMode::FADED;
	mtl.push_back("100000000");
	mtl.push_back("101000000");
	mtl.push_back("102000000");
	mtl.push_back("103000000");
	mtl.push_back("104000000");
	mtl.push_back("105000000");
	mtl.push_back("120000000");
	string map = "40000";//"180000000";//"login";
	string path = argv[0];
	path.erase(path.find_last_of("\\")+1);
	for (auto i = 0; i < argc; i++) {
		if (argv[i] == "-map") {
			map = argv[i+1];
			i++;
		} else if (argv[i] == "-path") {
			path = argv[i+1];
			i++;
		} else {

		}
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
		exit(3);
	}
	init_graphics();
	Mix_Init(0xf);
	Mouse::init();
	stats::init();
	nlstime.start();
	cout << "Initialization completed!" << endl;
	Map::Load(map,"");
	Map::Load();
	DevPortals = false;
	Running = true;
	fps = 100;
	tdelta = 0;
	alpha = 1;
	last_delta = nlstime.getElapsedTimeInMilliSec();
	return true;
}

bool Game::loop() {
	Input::Handle();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);

	//Wheeeeeeeee
	if (mindfuck) {
		glMatrixMode(GL_PROJECTION);
		if (random(1)>0.98) {
			glLoadIdentity();
			glOrtho(0,800,600,0,-1,1);
		}
		if (random(1)>0.95) {
			glRotated(random(360),0,0,1);
		}
		if (random(1)>0.95) {
			glTranslated(random(100),random(100),0);
		}
		glMatrixMode(GL_MODELVIEW);
	}
	glLoadIdentity();
	view.step();
	//Sorting objects
	if (resort){
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
#ifdef _DEBUG
	for (auto i = ladders.begin(); i != ladders.end(); i++) {
		(*i)->draw();
	}
	for (auto i = footholds.begin(); i != footholds.end(); i++) {
		(*i)->draw();
	}
#endif
	OpenGL::drawText("fps: " + tostring((int)fps), 0, 0, 12);
	OpenGL::drawText("Character: x: " + tostring((int)view.tx+400) + " | y: " + tostring((int)view.ty+350), 0, 16, 12);
	OpenGL::drawText("Mouse: x: " + tostring(Mouse::x) + " | y: " + tostring(Mouse::y), 0, 32, 12);
	OpenGL::drawText("Map ID: " + Map::currentmap, 0, 48, 12);
	// DrawableText test...
	OpenGL::drawText(DrawableText("Life: " + tostring(lifes.size()) + ", (NPCs: " + tostring(npcs.size()) + " | Mobs: " + tostring(mobs.size()) + ")", 0, 64, 12, "arial", TTF_STYLE_ITALIC));

	Mouse::draw();
	//Time stuff
	double temp = nlstime.getElapsedTimeInMilliSec();
	delta = temp - last_delta;
	delta = min(delta,(double)100);
	tdelta += delta;
	last_delta = temp;
	fps = (1000/max(delta,1.0)+fps*9)/10;
	if (loadtime) {
		cout << "Loading time was " << int(nlstime.getElapsedTimeInMilliSec()-loadtime) << "ms" << endl;
		loadtime = 0;
	}
	if (Map::nextmap != "" && Mode != RenderMode::FADED) {
		Mode = RenderMode::FADEIN;
	}
	switch (Mode) {
	case RenderMode::FADEIN: 
		if (alpha>=1) {
			Mode = RenderMode::FADED;
			alpha = 1;
		} else {
			alpha += delta/1000;
		}
		break;
	case RenderMode::FADEOUT: 
		if (alpha<=0) {
			Mode = RenderMode::NORMAL;
			alpha = 0;
		} else {
			alpha -= delta/1000;
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
	if (alpha>0) {
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
	TTF_Quit();
}