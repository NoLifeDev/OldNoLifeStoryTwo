////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Portal {
	public:
		void Draw();
		static void Load(Node n);
		static void Update();
		int x, y;
		int id;
		int pt;
		string tm, pn, tn;
		int hi, vi;
		string script;
		int onlyonce;
		int delay;
		int hidetooltip;
		bool close;
		NameTag derp;
		static set<Portal*> All;
		static set<Portal*>::iterator begin() {return All.begin();}
		static set<Portal*>::iterator end() {return All.end();}
		enum PhPortalStates {
			Nothing,
			Start,
			Continue,
			Exit
		} phState;
	};
}
