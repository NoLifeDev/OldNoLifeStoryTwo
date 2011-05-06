///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

void Element::Draw(int dx, int dy) {
	for (auto it = children.begin(); it != children.end(); it++) {
		it->Draw(dx+it->x, dy+it->y);
	}
}

bool Element::HandleKey(int key) {
	for (auto it = children.rbegin(); it != children.rend(); it++) {
		if (it->HandleKey(key)) {
			return true;
		}
	}
	return false;
}

bool Element::HandleMouse(int dx, int dy, Mouse::Action action) {
	for (auto it = children.rbegin(); it != children.rend(); it++) {
		if (it->HandleMouse(dx-it->x, dy-it->y, action)) {
			return true;
		}
	}
	return false;
}