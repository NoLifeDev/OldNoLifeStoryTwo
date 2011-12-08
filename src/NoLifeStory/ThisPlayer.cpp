////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::_ThisPlayer* NLS::ThisPlayer;

NLS::_ThisPlayer::_ThisPlayer() : Player() {
	pdelay = 0;
	control = true;
}

void NLS::_ThisPlayer::Draw() {
	left = Key::Left;
	right = Key::Right;
	up = Key::Up;
	down = Key::Down;
	Player::Draw();
	View::Follow(x, y);
	pdelay += Time::delta;
	for_each(Portal::begin(), Portal::end(), [&](Portal* p){
		if (x+50 > p->x and x-50 < p->x and y+50 > p->y and y-50 < p->y) {
			if (p->pt == 3 or p->pt == 9) {
				if (p->tm != "999999999" or p->tn != "") {
					Map::Load(p->tm, p->tn);
				}
			}
			if (vy > 0 and (p->vi or p->hi)) {
				vy = -p->vi;
				f?(vx=p->hi):(vx=-p->hi);
			}
		}
	});

	static int nextFlush = 0;
	int32_t now = clock();
	// 500 msecs for new change
	if (now - 500 >= nextFlush) {
		nextFlush = now;
		if (ThisPlayer->moves.size() > 0) {
			Send::PlayerMove();
		}
	}
}

void NLS::_ThisPlayer::UsePortal() {
	if (pdelay < 0.4) return;
	if (lr) return;
	for_each(Portal::begin(), Portal::end(), [&](Portal* p){
		if (x+50 > p->x and x-50 < p->x and y+50 > p->y and y-50 < p->y) {
			if (p->tm != "999999999" or p->tn != "") {
				Map::Load(p->tm, p->tn);
				pdelay = 0;
			}
		}
	});
}