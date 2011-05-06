///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

int& depth::operator [](unsigned int index) {
	return z[index];
}

void depth::operator =(int value) {
	z[size] = value;
	size++;
}

depth::depth() {
	size = 0;
	for(auto i = 0; i < maxDepth; i++) {
		z[i] = 0;
	}
}