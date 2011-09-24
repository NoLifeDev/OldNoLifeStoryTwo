////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Reactor {
	public:
		static void Load(Node n);
		void Draw();
		static vector <Reactor*> Reactors;
	};
};