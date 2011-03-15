///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

int Mouse::x;
int Mouse::y;
Mouse::State Mouse::state;
int Mouse::index;
int Mouse::delay;

void Mouse::init() {
	x = 0;
	y = 0;
	state = Mouse::NORMAL;
	index = 0;
	delay = 0;
}

void Mouse::draw() {
	wz::node main = wz::top["UI"]["Basic"]["Cursor"][tostring(state)];
	wz::node node = main[tostring(index)];
	if (node["delay"]) {
		int rdelay = node["delay"];
		if (rdelay == 0) {
			rdelay = 100;
		}
		delay += delta;
		if (delay > rdelay) {
			delay = 0;
			index++;
			if (!main[tostring(index)]) {
				index = 0;
			}
			node = main[tostring(index)];
		}
	}
	Sprite(node).Draw(Mouse::x, Mouse::y, false);
}

void Mouse::CheckPosition() {
	if (state==State::PRESSED or state==State::PRESSED_GRAB
		or state==State::PRESSED_NPC or state==State::PRESSED_SCROLLBAR_VERTICAL
		or state==State::PRESSED_SCROLLBAR_HORIZONTAL or state==State::PRESSED_MAGNIFYING_GLASS) {
			return;
	}
	int tmpx = Mouse::x+view.x;
	int tmpy = Mouse::y+view.y;
	bool found = false;
	for (auto i = 0; i < npcs.size(); i++) {
		npc *l = npcs[i];
		if (l == nullptr) {
			continue;
		}
		if (tmpx>=l->bl && tmpx<=l->br) {
			if (tmpy>=l->bt && tmpy<=l->bb) {
				found = true;
			}
		}
	}
	if (found) {
		SetState(State::PRESSABLE_NPC);
	} else {
		SetState(State::NORMAL);
	}
}

void Mouse::SetState(Mouse::State newstate) {
	if (state!=newstate) {
		delay = 0;
		index = 0;
		state = newstate;
	}
}