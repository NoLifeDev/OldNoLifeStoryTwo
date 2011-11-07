////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Reactor {
	public:
		static void Load(Node n);
		void Draw();
		int x, y;
		int time;
		string id, name;
		Node data;
		bool f;
		static vector <Reactor*> Reactors;
	};
}
