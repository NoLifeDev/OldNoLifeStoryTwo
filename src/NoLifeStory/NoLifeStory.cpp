////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

int main(int argc, uchar **argv) {
	NLS::Init(vector<ustring>(argv, argv+argc));
	while (NLS::Loop()) {}
	NLS::Unload();
	return 0;
}
