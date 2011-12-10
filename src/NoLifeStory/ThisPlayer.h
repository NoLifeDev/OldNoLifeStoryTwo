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
		void TryNpcChat();
		double pdelay;
		uint8_t currentPortal;
		MapleRNG damageRNG;
	};
	extern _ThisPlayer* ThisPlayer;
}
