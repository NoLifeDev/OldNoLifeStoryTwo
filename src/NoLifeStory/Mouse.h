////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace Mouse {
		void Init();
		void HandleEvent(sf::Event&);
		void Draw();
		enum MState {
			Normal,
			OnOverGrab,
			OnOverClickable,
			OnOverClickableMinigame,
			OnOverClickablePersonalShop,
			OnOverScrollbarHorizontal,
			OnOverScrollbarVertical,
			OnOverScrollbarHorizontalLocked,
			OnOverScrollbarVerticalLocked,
			Grabbed,
			OnOverClickableLocked,
		};
		extern MState State;
		extern int x, y;
	}
}