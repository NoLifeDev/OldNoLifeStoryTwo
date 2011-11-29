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
		int8_t id;
		int pt;
		string tm, pn, tn;
		int hi, vi;
		string script;
		int onlyonce;
		int delay;
		int hidetooltip;
		bool close;
		static vector <Portal*> Portals;
	};
}
