////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class KeyAction {
	public:
		KeyAction();
		KeyAction(function<void(void)>);
		function<void(void)> action;
		void operator() () {
			if (action) {
				return action();
			}
		}
	};
	void KeySet(sf::Keyboard::Key, function<void(void)>);
	extern map <sf::Keyboard::Key, KeyAction> KeyMap;
}
#define Func(x) [&](){x();}