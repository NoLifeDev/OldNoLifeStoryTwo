////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"
unsigned short port = 10273;
int main(int argc, char **argv) {
#ifdef NLS_WINDOWS
	SetConsoleTitleA("NoLifeServer::Console");
#endif
	cout << "INFO: Initializing NoLifeServer" << endl;
	vector<string> strs(argv, argv+argc);
	NLS::Init(strs);
	NLS::Loop();
	NLS::Unload();
	return 0;
}