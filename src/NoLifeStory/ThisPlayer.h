////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class _ThisPlayer : public Player {//The player that you control
	public:
		_ThisPlayer();
		void Draw();
		void UsePortal();
		void CheckEmoteKey();
		double pdelay;
		uint8_t currentPortal;
	};
	extern _ThisPlayer* ThisPlayer;
}
