////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::_Time NLS::Time;

void NLS::_Time::Reset() {
#ifdef NLS_CPP11
	last = clock.now();
	start = clock.now();
#else
	clock.Reset();
#endif
	delta = 0;
	tdelta = 0;
	fps = 0;
	output = true;
}

void NLS::_Time::Step() {
#ifdef NLS_CPP11
	chrono::high_resolution_clock::time_point now = clock.now();
	chrono::duration<double> dif = now-last;
	chrono::duration<double> tdif = now-start;
	delta = dif.count();
	tdelta = tdif.count();
#else
	double temp = clock.GetElapsedTime();
	temp /= 1000;
	delta = temp-tdelta;
	tdelta = temp;
#endif
	fps = fps*0.99+1/min(delta, 0.01)*0.01;
#ifdef NLS_CPP11
	this_thread::sleep_for(chrono::duration<double>(min(max(fps-100, 0.), 10.)/1000));
#else
	sf::Sleep(min(max(fps-100, 0.), 10.));
#endif
	if (output) {
		C("INFO") << "Time taken: " << floor(delta/1000) << " ms" << endl;
		output = false;
	}
	delta = min(0.1, delta);
}
