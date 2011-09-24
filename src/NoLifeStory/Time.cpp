////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::_Time NLS::Time;

void NLS::_Time::Reset() {
	clock.Reset();
	delta = 0;
	tdelta = 0;
	fps = 0;
	output = true;
}

void NLS::_Time::Step() {
	uint32_t temp = clock.GetElapsedTime();
	delta = temp-tdelta;
	tdelta = temp;
	fps = fps*0.99 + (1000/(double)max(delta, 1))*0.01;
	sf::Sleep(min(max(fps-100, 0), 10));
	if (output) {
		C("INFO") << "Time taken: " << delta << " ms" << endl;
		output = false;
	}
}