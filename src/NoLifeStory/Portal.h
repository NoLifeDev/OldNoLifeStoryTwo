////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////
namespace NLS {
	class Portal {
	public:
		void Draw();
		static void Load(Node n);
		int x, y;
		int pt, tm;
		ustring pn, tn;
		int hi, vi;
		ustring script;
		int onlyonce;
		int delay;
		int hidetooltip;
		bool close;
		static vector <Portal*> Portals;
	};
}
