///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////

namespace KeyMap {
	typedef struct _KeyMapping {
		int type;
		int action;
	} *PKeyMapping, KeyMapping;
	
	// TYPE, ACTION
	// RETURN -1 on failure, keysym on success
	int getMappedKey(int, int);

	// SYM, TYPE, ACTION
	bool mapKey(int, int, int);

	// SYM
	PKeyMapping getActionFor(int);

}