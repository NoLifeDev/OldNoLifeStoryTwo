////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Reactor {
	public:
		static void Load(Node n);
		void Draw();
		bool f;
		int x, y;
		int time;
		string id, name;
		Node data;
		static vector <Reactor*> Reactors;
	};
};