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
}

void NLS::_Time::Step() {
	double temp = clock.GetElapsedTime();
	delta = temp-tdelta;
	tdelta = temp;
}