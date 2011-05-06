///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace Mouse {
	enum Action {
		Press,
		Release,
		Move
	};
	enum State { 
		NORMAL, 
		PRESSABLE_NPC, 
		PRESSABLE_MINIGAME,
		PRESSABLE_HOUSE, 
		PRESSABLE_CLICK,
		PRESSABLE_GRAB,
		PRESSABLE_CASHSHOP_BUY, 
		PRESSABLE_SCROLLBAR_VERTICAL,
		PRESSABLE_SCROLLBAR_HORIZONTAL,
		PRESSED_SCROLLBAR_VERTICAL,
		PRESSED_SCROLLBAR_HORIZONTAL,
		PRESSED_GRAB,
		PRESSED,
		PRESSED_NPC,
		NORMAL_MAGNIFYING_GLASS,
		PRESSABLE_MAGNIFYING_GLASS,
		PRESSED_MAGNIFYING_GLASS,
	};

	extern int index;
	extern int x;
	extern int y;
	extern int delay;
	extern Mouse::State state;
	
	void init();

	void draw();
	void SetState(Mouse::State state);
	void CheckPosition();
}