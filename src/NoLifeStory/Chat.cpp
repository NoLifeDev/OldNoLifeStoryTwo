////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::ChatLog NLS::Messenger;
NLS::ChatLog NLS::MainChat;

void NLS::ChatLog::Clear() {
	Messages.clear();
}