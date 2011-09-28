////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
#include "Global.h"

NLS::Sound::Sound() {
	stream = 0;
	data = 0;
}

NLS::Sound::Sound(const Sound& other) {
	data = other.data;
	stream = 0;
}

NLS::Sound::Sound(SoundProperty* data) {
	this->data = data;
	stream = 0;
}

NLS::Sound& NLS::Sound::operator= (const Sound& other) {
	if (stream) {
		BASS_StreamFree(stream);
	}
	data = other.data;
	stream = 0;
	return *this;
}

NLS::Sound::~Sound() {
	if (stream) {
		BASS_StreamFree(stream);
	}
}

void NLS::Sound::Play(bool loop) {
	if (!stream) {
		stream = data->GetStream(loop);
	}
	BASS_ChannelPlay(stream, !loop);
}

void NLS::Sound::Stop() {
	BASS_ChannelStop(stream);
}