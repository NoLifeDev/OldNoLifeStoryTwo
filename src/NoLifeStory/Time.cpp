////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

#ifdef NLS_CPP11
chrono::high_resolution_clock tclock;
chrono::high_resolution_clock::time_point start;
#else
sf::Clock tclock;
#endif
bool output;
double NLS::Time::delta;
double NLS::Time::tdelta;
double NLS::Time::fps;

void NLS::Time::Reset() {
#ifdef NLS_CPP11
	start = tclock.now();
#else
	tclock.Reset();
#endif
	delta = 0;
	tdelta = 0;
	fps = 0;
	output = true;
}

void NLS::Time::Step() {
#ifdef NLS_CPP11
	chrono::high_resolution_clock::time_point now = tclock.now();
	chrono::duration<double> dif = now-start;
	delta = dif.count()-tdelta;
	tdelta = dif.count();
#else
	double temp = tclock.GetElapsedTime();
	temp /= 1000;
	delta = temp-tdelta;
	tdelta = temp;
#endif
	fps = fps*0.98+1/max(delta, 0.001)*0.02;
	if (fps < 0 or fps > 1000) {
		fps = 0;
	}
#ifdef NLS_CPP11
	this_thread::sleep_for(chrono::milliseconds(min(max((int)fps-100, 0), 10)));
#else
	sf::Sleep(min(max(fps-100, 0.), 10.));
#endif
	if (output) {
		cout << "Time taken: " << floor(delta*1000) << " ms" << endl;
		output = false;
	}
	delta = min(0.1, delta);
}
