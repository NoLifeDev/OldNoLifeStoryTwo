///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

extern NLS::LoginServer* loginServer;

namespace NLS {
	void Init(vector<string> args);
	bool Loop();
	void Unload();
};