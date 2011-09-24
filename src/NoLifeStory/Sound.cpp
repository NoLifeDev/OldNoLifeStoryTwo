////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Sound::Sound() {
	stream = 0;
}

void NLS::Sound::Play(bool loop) {
	if (!stream) {
		if (loop) {
			stream = BASS_StreamCreateFile(true, data->data, 0, data->len, BASS_SAMPLE_FLOAT|BASS_SAMPLE_LOOP);
		} else {
			stream = BASS_StreamCreateFile(true, data->data, 0, data->len, BASS_SAMPLE_FLOAT);
		}
	}
	BASS_ChannelPlay(stream, !loop);
}

void NLS::Sound::Stop() {
	BASS_ChannelStop(stream);
}

void NLS::Sound::operator = (Node n) {
	if (data == n.data->sound) {
		return;
	}
	if (stream) {
		BASS_StreamFree(stream);
		stream = 0;
	}
	data = n.data->sound;
}