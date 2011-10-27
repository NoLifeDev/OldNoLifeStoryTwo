////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::_ThisPlayer NLS::ThisPlayer;

NLS::_ThisPlayer::_ThisPlayer() {
	KeySet(sf::Keyboard::F, Func(MouseFly));
}