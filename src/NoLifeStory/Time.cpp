////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::_Time NLS::Time;

void NLS::_Time::Reset() {
	last = clock.now();
	start = clock.now();
	delta = 0;
	tdelta = 0;
	fps = 0;
	output = true;
}

void NLS::_Time::Step() {
	chrono::high_resolution_clock::time_point now = clock.now();
	chrono::duration<double> dif = now-last;
	chrono::duration<double> tdif = now-start;
	delta = dif.count();
	tdelta = tdif.count();
	fps = fps*0.99+1/min(delta, 0.01)*0.01;
	this_thread::sleep_for(chrono::duration<double>(min(max(fps-100, 0.), 10.)/1000));
	if (output) {
		C("INFO") << "Time taken: " << floor(delta/1000) << " ms" << endl;
		output = false;
	}
	delta = min(0.1, delta);
}
