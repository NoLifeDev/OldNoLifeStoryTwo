////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Sound {
	public:
		Sound();
		Sound(const Sound&);
		Sound(SoundProperty* data);
		Sound& operator= (const Sound&);
		~Sound();
		void Play(bool loop = false);
		void Stop();
	private:
		uint32_t stream;
		SoundProperty* data;
	};
};