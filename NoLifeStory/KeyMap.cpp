///////////////////////////////////////////////
// This file is part of NoLifeStory.         //
// Please see Global.h for more information. //
///////////////////////////////////////////////
#include "Global.h"

namespace KeyMap {

	std::map<int, PKeyMapping> keymap;

	int getMappedKey(int type, int action) {
		auto i = keymap.begin();
		while (i != keymap.end()) {
			std::pair<int, PKeyMapping> _map = *i;
			if (_map.second != NULL) {
				if (_map.second->action == action && _map.second->type == type) {
					return _map.first;
				}
			}
			i++;
		}

		return -1;
	}

	bool mapKey(int sym, int type, int action) {
		PKeyMapping _map = (PKeyMapping) nlsMalloc(sizeof(_KeyMapping));
		_map->type = type;
		_map->action = action;
		keymap [ sym ] = _map;
		return true;
	}

	PKeyMapping getActionFor(int sym) {
		std::map<int, PKeyMapping>::iterator i = keymap.find(sym);
		if (i == keymap.end()) {
			return NULL;
		}
		std::pair<int, PKeyMapping> _map = *i;
		return i->second;
	}

}