////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	namespace Mouse {
		void Init();
		void Draw();
		void HandleMouseMove(sf::Event::MouseMoveEvent &);

		enum Statusses {
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
		extern int mouseX, mouseY, Status;
	}
}