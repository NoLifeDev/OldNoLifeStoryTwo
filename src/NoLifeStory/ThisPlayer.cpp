////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::_ThisPlayer* NLS::ThisPlayer;

NLS::_ThisPlayer::_ThisPlayer() : Player() {
	pdelay = 0;
}

void NLS::_ThisPlayer::Draw() {
	left = sf::Keyboard::IsKeyPressed(sf::Keyboard::Left);
	right = sf::Keyboard::IsKeyPressed(sf::Keyboard::Right);
	up = sf::Keyboard::IsKeyPressed(sf::Keyboard::Up);
	down = sf::Keyboard::IsKeyPressed(sf::Keyboard::Down);
	Player::Draw();
	View::tx = x;
	View::ty = y;
	pdelay += Time::delta;
	for (auto it = Portal::Portals.begin(); it != Portal::Portals.end(); it++) {
		Portal& p = **it;
		if (x+50 > p.x and x-50 < p.x and y+50 > p.y and y-50 < p.y) {
			if (p.pt == 3 or p.pt == 9) {
				if (p.tm != "999999999" or p.tn != "") {
					Map::Load(p.tm, p.tn);
				}
			}
			if (vy > 0) {
				vy += p.vi;
				if (f) {
					vx += p.hi;
				} else {
					vx -= p.hi;
				}
			}
		}
	}
}

void NLS::_ThisPlayer::UsePortal() {
	if (pdelay < 0.4) return;
	if (lr) return;
	for (auto it = Portal::Portals.begin(); it != Portal::Portals.end(); it++) {
		Portal& p = **it;
		if (x+50 > p.x and x-50 < p.x and y+50 > p.y and y-50 < p.y) {
			if (p.tm != "999999999" or p.tn != "") {
				Map::Load(p.tm, p.tn);
				pdelay = 0;
			}
		}
	}
}