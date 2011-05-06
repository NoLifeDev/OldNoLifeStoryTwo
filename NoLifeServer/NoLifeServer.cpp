////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

int main(int argc, char **argv) {//Not much to do here
#ifdef NLS_WINDOWS
	SetConsoleTitleA("NoLifeServer::Console");
#endif
	cout << "Loading NoLifeServer..." << endl;
	vector<string> strs(argv, argv+argc);
	//Actually run NLS here
	NLS::Init(strs);
	while (NLS::Loop()) {}
	NLS::Unload();
	return 0;
}