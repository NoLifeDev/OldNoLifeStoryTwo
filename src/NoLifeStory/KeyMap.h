////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class KeyAction {
	public:
		void (*action)();
		void operator() () {
			return action();
		}
	};
	extern map <sf::Keyboard::Key, KeyAction> KeyMap;
}
