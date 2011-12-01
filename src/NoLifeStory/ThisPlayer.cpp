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
	left = sf::Keyboard::IsKeyPressed(sf::Keyboard::Left);
	right = sf::Keyboard::IsKeyPressed(sf::Keyboard::Right);
	up = sf::Keyboard::IsKeyPressed(sf::Keyboard::Up);
	down = sf::Keyboard::IsKeyPressed(sf::Keyboard::Down);
	Player::Draw();
	View::tx = x;
	View::ty = y;
	pdelay += Time::delta;
	for_each(Portal::begin(), Portal::end(), [&](Portal* p){
		if (x+50 > p->x and x-50 < p->x and y+50 > p->y and y-50 < p->y) {
			if (p->pt == 3 or p->pt == 9) {
				if (p->tm != "999999999" or p->tn != "") {
					Map::Load(p->tm, p->tn);
				}
			}
			if (vy > 0) {
				vy += p->vi;
				if (f) {
					vx += p->hi;
				} else {
					vx -= p->hi;
				}
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

void NLS::_ThisPlayer::CheckEmoteKey() {
	if (lastEmote != "default") return; // Remove this for emote spam!
	if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F1)) emote = GetEmoteNameByID(1);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F2)) emote = GetEmoteNameByID(2);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F3)) emote = GetEmoteNameByID(3);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F4)) emote = GetEmoteNameByID(4);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F5)) emote = GetEmoteNameByID(5);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F6)) emote = GetEmoteNameByID(6);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F7)) emote = GetEmoteNameByID(7);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F8)) emote = GetEmoteNameByID(8);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F8)) emote = GetEmoteNameByID(9);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F10)) emote = GetEmoteNameByID(10);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F11)) emote = GetEmoteNameByID(11);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::F12)) emote = GetEmoteNameByID(12);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num1)) emote = GetEmoteNameByID(13);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num2)) emote = GetEmoteNameByID(14);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num3)) emote = GetEmoteNameByID(15);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num4)) emote = GetEmoteNameByID(16);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num5)) emote = GetEmoteNameByID(17);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num6)) emote = GetEmoteNameByID(18);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num7)) emote = GetEmoteNameByID(19);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num8)) emote = GetEmoteNameByID(20);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num9)) emote = GetEmoteNameByID(21);
	else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Num0)) emote = GetEmoteNameByID(22);
}