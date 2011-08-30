////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

void NLS::Init(vector<string> args) {
	Network::Init();
	Time.Reset();
	WZ::Init("C:\\Nexon\\MapleStory\\");
	Time.Step();
	cout << "Initializing WZ data took: " << Time.tdelta << " seconds!" << endl;
	Time.Reset();
	Map::Load("100000000", "");
	Map::Load();
}

bool NLS::Loop() {
	static uint64_t counter(0);
	static double fps;
	Time.Step();
	fps += Time.delta;
	counter++;
	if (counter%1000000 == 0) {
		cout << 1000000/fps << endl;
		fps = 0;
	}
	return false;
}

void NLS::Unload() {

}