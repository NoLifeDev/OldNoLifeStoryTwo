////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Key {
		class Action {
		public:
			Action();
			Action(function<void()>);
			function<void()> action;
			void operator() () {
				if (action) {
					return action();
				}
			}
		};
		void Init();
		void Set(sf::Keyboard::Key, function<void()>);
		extern map <sf::Keyboard::Key, Action> Map;
		void Handle(sf::Event);
		extern bool Left, Right, Up, Down;
	}
}
#define Func(x) [&](){x();}