////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Sound {
	public:
		Sound();
		void Play(bool loop = false);
		void Stop();
		void operator = (Node);
		uint32_t stream;
		WZ::SoundProperty* data;
	};
};