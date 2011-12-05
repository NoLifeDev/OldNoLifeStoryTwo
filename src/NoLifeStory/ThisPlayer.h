////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class _ThisPlayer : public Player {
	public:
		_ThisPlayer();
		void Draw();
		void UsePortal();
		double pdelay;
		uint8_t currentPortal;
	};
	extern _ThisPlayer* ThisPlayer;
}
