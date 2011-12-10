////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace Mouse {
		void Init();
		void HandleEvent(sf::Event&);
		void Draw();
		enum StateEnum {
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
		extern StateEnum State;
		extern int x, y;
		extern UI::Element* over;
		extern int cx, cy;
	}
}