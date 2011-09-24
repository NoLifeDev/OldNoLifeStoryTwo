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
		bool close;
		int pt, tm;
		string pn, tn;
		int hi, vi;
		string script;
		int onlyonce;
		int delay;
		int hidetooltip;
		static vector <Portal*> Portals;
	};
};