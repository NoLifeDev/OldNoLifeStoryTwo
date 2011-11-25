////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace Mouse {
		void Init();
		inline void HandleEvent(sf::Event) {}
		void Draw();
		void HandleMouseMove(sf::Event::MouseMoveEvent &);

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