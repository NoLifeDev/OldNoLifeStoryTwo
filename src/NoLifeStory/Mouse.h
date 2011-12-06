////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Grab {

	};
	namespace Mouse {
		void Init();
		void HandleEvent(sf::Event&);
		void Draw();
		enum MState {
			Normal,
			OnOverClickable,
			OnOverClickableMinigame,
			OnOverClickablePersonalShop,
			OnOverClickable2,
			OnOverGrab,
			OnOverGift,
			OnOverScrollbarVertical,
			OnOverScrollbarHorizontal,
			OnOverScrollbarVerticalLocked,
			OnOverScrollbarHorizontalLocked,
			Grabbed,
			OnOverClickableLocked,
			OnOverClickable3,
			Total
		};
		extern MState State;
		extern int x, y;
		extern int grabx, graby;
		extern Grab grabbing;
	}
}