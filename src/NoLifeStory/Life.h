////////////////////////////////////////////////////
// This file is part of NoLifeStory.              //
// Please see SuperGlobal.h for more information. //
////////////////////////////////////////////////////

namespace NLS {
	class Life {
	public:
		static void Load();
		void Init();
		void Draw();
		void Update();
		void ChangeState(const string &);
		int x, y, cx, cy, rx0, rx1;
		int time;
		string id, type, defaultState, currentState;
		Node data;

		AniSprite currentAnimation;
		bool f, hide;
		static vector <Life *> Lifes;
	};
}