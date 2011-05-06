///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

sound_data::sound_data() {
	data = 0;
	loaded = false;
}

sound::sound() {
	data = 0;
}

void sound::operator =(WZLib_SoundProperty* mp3) {
	data = new sound_data;
	data->data = mp3;
}

void sound::play() {
	if (data) {
		if (!data->loaded) {
			data->loaded = true;
		}
		WZLib_SoundProperty_Play(data->data);
	}
}