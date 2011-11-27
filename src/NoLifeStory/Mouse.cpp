////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::AniSprite normal;
NLS::AniSprite onOverGrab;
NLS::AniSprite onOverGift;
NLS::AniSprite onOverClickable;
NLS::AniSprite onOverClickableMinigame;
NLS::AniSprite onOverClickablePersonalShop;
NLS::AniSprite onOverScrollbarHorizontal;
NLS::AniSprite onOverScrollbarVertical;
NLS::AniSprite onOverScrollbarHorizontalLocked;
NLS::AniSprite onOverScrollbarVerticalLocked;
NLS::AniSprite grabbed;
NLS::AniSprite onOverClickableLocked;

int NLS::Mouse::x = 0;
int NLS::Mouse::y = 0;
NLS::Mouse::MState NLS::Mouse::State = NLS::Mouse::Normal;

void NLS::Mouse::Init() {
	Node base = WZ["UI"]["Basic"]["Cursor"];
	normal.Set(base["0"]);
	onOverClickable.Set(base["1"]); // Same as 4 and 13 ?
	onOverClickableMinigame.Set(base["2"]);
	onOverClickablePersonalShop.Set(base["3"]);
	onOverGrab.Set(base["5"]);
	onOverGift.Set(base["6"]);
	onOverScrollbarVertical.Set(base["7"]);
	onOverScrollbarHorizontal.Set(base["8"]);
	onOverScrollbarVerticalLocked.Set(base["9"]);
	onOverScrollbarHorizontalLocked.Set(base["10"]);
	grabbed.Set(base["11"]);
	onOverClickableLocked.Set(base["12"]);
}

void NLS::Mouse::Draw() {
	NLS::AniSprite curSprite;
	switch (State) {
	case NLS::Mouse::Normal: curSprite = normal; break;
	case NLS::Mouse::Grabbed: curSprite = grabbed; break;
	case NLS::Mouse::OnOverClickable: curSprite = onOverClickable; break;
	case NLS::Mouse::OnOverClickableLocked: curSprite = onOverClickableLocked; break;
	default: curSprite = normal; break;
	}
	auto p = sf::Mouse::GetPosition(*window);
	x = p.x;
	y = p.y;
	curSprite.Draw(x, y);
}

void NLS::Mouse::HandleEvent(sf::Event& e) {
	switch (e.Type) {

	}
}