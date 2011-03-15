///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

class sound_data{
public:
	sound_data();
	WZLib_SoundProperty* data;
	bool loaded;
};
class sound{
public:
	sound();
	sound_data* data;
	void operator =(WZLib_SoundProperty* png);
	void play();
};