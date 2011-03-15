///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

bool Input::Key[1024];
void Input::Handle() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: Game::Running = false; break;
		case SDL_KEYDOWN: Key[event.key.keysym.sym] = true; break;
		case SDL_KEYUP: Key[event.key.keysym.sym] = false; break;
		case SDL_MOUSEMOTION:
			Mouse::x = event.motion.x;
			Mouse::y = event.motion.y;
			Mouse::CheckPosition();
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				Mouse::CheckPosition();
				// Needs checks where the mouse is...
				Mouse::SetState(Mouse::State::PRESSED);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				// Needs checks too.
				switch (Mouse::state) {
					case Mouse::State::PRESSED_SCROLLBAR_HORIZONTAL:
						Mouse::SetState(Mouse::State::PRESSABLE_SCROLLBAR_HORIZONTAL);
						break;
					case Mouse::State::PRESSED_SCROLLBAR_VERTICAL:
						Mouse::SetState(Mouse::State::PRESSABLE_SCROLLBAR_VERTICAL);
						break;
					case Mouse::State::PRESSED_NPC:
						Mouse::SetState(Mouse::State::PRESSABLE_NPC);
						break;
					case Mouse::State::PRESSED:
					case Mouse::State::PRESSED_GRAB:
						Mouse::SetState(Mouse::State::NORMAL);
						break;
				}
				Mouse::CheckPosition();
			}
			break;
		}
	}

	if (Key[SDLK_RETURN]) {
		string id;
		cout << "Enter command: " << endl;
		cin >> id;
		if (id == "zakum") {
			wz::node img = wz::top["Mob"]["8800002"];
			if (img["info"]["link"]) {
				img = wz::top["Mob"][(string)img["info"]["link"]];
			}
			mob* nlife = new mob;
			nlife->img = img;
			nlife->id = "8800002";
			int id = atoi(nlife->id.c_str());
			while(nlife->id.size()<7) {
				nlife->id = "0"+nlife->id;
			}
			nlife->x = theplayer->x;
			nlife->y = theplayer->y;
			nlife->f = false;
			nlife->mobtime = 0;
			nlife->init();
		}
		else {
			Map::Load(id,"");
		}
	}
}