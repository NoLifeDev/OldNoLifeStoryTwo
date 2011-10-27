////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

map <sf::Keyboard::Key, NLS::KeyAction> NLS::KeyMap;

NLS::KeyAction::KeyAction() {
	action = 0;
}
NLS::KeyAction::KeyAction(function<void(void)> f) {
	action = f;
}
void NLS::KeySet(sf::Keyboard::Key k, function<void(void)> f) {
	KeyMap[k] = f;
}