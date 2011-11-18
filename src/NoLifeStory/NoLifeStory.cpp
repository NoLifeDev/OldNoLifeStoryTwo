////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

int main(int argc, char **argv) {
	NLS::Init();
	while (NLS::Loop()) {}
	NLS::Unload();
	return 0;
}
