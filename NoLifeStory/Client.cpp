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
	cout << "Initializing wz data took: " << Time.tdelta << " seconds!" << endl;
	Time.Reset();
}

bool NLS::Loop() {
	Time.Step();
	cout << Time.delta << endl;
	return true;
}

void NLS::Unload() {

}