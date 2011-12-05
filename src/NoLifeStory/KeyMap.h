////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	namespace Key {
		void Init();
		void Set(sf::Keyboard::Key, function<void()>);
		extern map <sf::Keyboard::Key, function<void()>> Map;
		void Handle(sf::Event);
		extern bool Left, Right, Up, Down;
	}
}
#define Func(x) [&](){x();}