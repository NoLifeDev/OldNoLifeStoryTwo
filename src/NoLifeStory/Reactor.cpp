////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

vector <NLS::Reactor*> NLS::Reactor::Reactors;

void NLS::Reactor::Load(Node n) {
	for (auto it = Reactors.begin(); it != Reactors.end(); it++) {
		delete *it;
	}
	Reactors.clear();
	n = n["reactor"];
	if (n) {
		C("INFO") << "I FOUND REACTORS" << endl;
	}
}