///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

////////////////////////////////////////////////////////////////
// Welcome to NoLifeStory!
////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {//Not much to do here
	try {
#ifdef NLS_WINDOWS
		SetConsoleTitleA("NoLifeStory::Console");
#endif
		cout << "Loading NoLifeStory" << endl;
		string* strs = new string[argc];
		for (auto i=0; i<argc; i++) {
			strs[i] = argv[i];
			cout << strs[i] << endl;
		}
		Game::init(strs,argc);
		while(Game::loop()) {}
		Game::unload();
	}
	catch (exception &ex) {
		cout << ex.what() << endl;
		getchar();
	}
	return 0;
}